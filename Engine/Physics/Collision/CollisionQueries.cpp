#include "CollisionQueries.h"

#include <glm/glm.hpp>
#include <algorithm>
#include <array>
#include <cmath>

namespace
{
    constexpr float EPSILON = 1e-6f;

    glm::vec3 closestPointOnAABB(
        const glm::vec3& point,
        const AABB& box)
    {
        return glm::clamp(point, box.min, box.max);
    }

    bool intersectsAABB(
        const AABB& a,
        const AABB& b)
    {
        return
            a.min.x <= b.max.x && a.max.x >= b.min.x &&
            a.min.y <= b.max.y && a.max.y >= b.min.y &&
            a.min.z <= b.max.z && a.max.z >= b.min.z;
    }

    float segmentAABBDistanceSquared(
        const glm::vec3& a,
        const glm::vec3& b,
        const AABB& box,
        glm::vec3& segmentPoint,
        glm::vec3& boxPoint)
    {
        const glm::vec3 d = b - a;

        std::array<float, 8> points{};
        int pointCount = 0;

        points[pointCount++] = 0.0f;
        points[pointCount++] = 1.0f;

        for (int axis = 0; axis < 3; ++axis)
        {
            if (std::abs(d[axis]) <= EPSILON)
                continue;

            const float tMin =
                (box.min[axis] - a[axis]) / d[axis];

            const float tMax =
                (box.max[axis] - a[axis]) / d[axis];

            if (tMin > 0.0f && tMin < 1.0f)
                points[pointCount++] = tMin;

            if (tMax > 0.0f && tMax < 1.0f)
                points[pointCount++] = tMax;
        }

        std::sort(
            points.begin(),
            points.begin() + pointCount);

        // Remove duplicate breakpoints.
        int uniqueCount = 0;

        for (int i = 0; i < pointCount; ++i)
        {
            if (uniqueCount == 0 ||
                std::abs(
                    points[i] -
                    points[uniqueCount - 1]) > EPSILON)
            {
                points[uniqueCount++] = points[i];
            }
        }

        float bestDistanceSq = INFINITY;
        float bestT = 0.0f;

        auto evaluate = [&](float t)
        {
            const glm::vec3 p =
                a + d * t;

            const glm::vec3 q =
                closestPointOnAABB(p, box);

            const glm::vec3 delta =
                p - q;

            const float distanceSq =
                glm::dot(delta, delta);

            if (distanceSq < bestDistanceSq)
            {
                bestDistanceSq = distanceSq;
                bestT = t;
            }
        };

        // Evaluate all breakpoints.
        for (int i = 0; i < uniqueCount; ++i)
            evaluate(points[i]);

        /*
            On each interval the set of active box faces is constant.

            Therefore:

                distanceVector(t) = c + m * t

            and:

                distanceSq(t) =
                    dot(c + m*t, c + m*t)

            Its minimum is found analytically.
        */
        for (int i = 0; i + 1 < uniqueCount; ++i)
        {
            const float left = points[i];
            const float right = points[i + 1];

            if (right - left <= EPSILON)
                continue;

            const float mid =
                (left + right) * 0.5f;

            const glm::vec3 pMid =
                a + d * mid;

            glm::vec3 c{};
            glm::vec3 m{};

            for (int axis = 0; axis < 3; ++axis)
            {
                if (pMid[axis] < box.min[axis])
                {
                    // p(t) - box.min
                    c[axis] =
                        a[axis] - box.min[axis];

                    m[axis] =
                        d[axis];
                }
                else if (pMid[axis] > box.max[axis])
                {
                    // p(t) - box.max
                    c[axis] =
                        a[axis] - box.max[axis];

                    m[axis] =
                        d[axis];
                }
                else
                {
                    // Inside the box along this axis.
                    c[axis] = 0.0f;
                    m[axis] = 0.0f;
                }
            }

            const float denominator =
                glm::dot(m, m);

            float t = left;

            if (denominator > EPSILON)
            {
                /*
                    Minimize:

                        |c + m*t|^2

                    derivative:

                        2 * dot(c + m*t, m) = 0

                    therefore:

                        t = -dot(c,m) / dot(m,m)
                */
                t =
                    -glm::dot(c, m) /
                    denominator;

                t =
                    glm::clamp(
                        t,
                        left,
                        right);
            }

            evaluate(t);
        }

        segmentPoint =
            a + d * bestT;

        boxPoint =
            closestPointOnAABB(
                segmentPoint,
                box);

        return bestDistanceSq;
    }
}

bool sweepCapsuleVsAABB(
    const Capsule& capsule,
    const AABB& box,
    const glm::vec3& displacement,
    CollisionHit& hit)
{
    hit = {};

    const float radiusSq =
        capsule.radius * capsule.radius;

    /*
        Broad phase.

        The capsule is approximated by the AABB containing
        both its initial and final positions, expanded by radius.
    */
    const glm::vec3 sweptMin =
        glm::min(
            glm::min(capsule.a, capsule.b),
            glm::min(
                capsule.a + displacement,
                capsule.b + displacement))
        - glm::vec3(capsule.radius);

    const glm::vec3 sweptMax =
        glm::max(
            glm::max(capsule.a, capsule.b),
            glm::max(
                capsule.a + displacement,
                capsule.b + displacement))
        + glm::vec3(capsule.radius);

    const AABB sweptBox{
        sweptMin,
        sweptMax
    };

    if (!intersectsAABB(sweptBox, box))
        return false;

    /*
        Check initial position first.

        This is important because the capsule may already be
        penetrating the box before it starts moving.
    */
    glm::vec3 initialSegmentPoint;
    glm::vec3 initialBoxPoint;

    const float initialDistanceSq =
        segmentAABBDistanceSquared(
            capsule.a,
            capsule.b,
            box,
            initialSegmentPoint,
            initialBoxPoint);

    if (initialDistanceSq <= radiusSq) {
        hit.hit = true;
        hit.fraction = 0.0f;
        hit.point = initialBoxPoint;

        const glm::vec3 initialNormal =
    initialSegmentPoint - initialBoxPoint;

        const float initialDistance =
            std::sqrt(initialDistanceSq);

        if (initialDistance < capsule.radius - EPSILON)
        {
            hit.hit = true;
            hit.fraction = 0.0f;
            hit.point = initialBoxPoint;

            if (glm::dot(initialNormal, initialNormal) > EPSILON)
            {
                hit.normal =
                    glm::normalize(initialNormal);
            }
            else
            {
                hit.normal = glm::vec3(0.0f, 1.0f, 0.0f);
            }

            return true;
        }

        if (std::abs(initialDistance - capsule.radius) <= EPSILON)
        {
            glm::vec3 normal;

            if (glm::dot(initialNormal, initialNormal) > EPSILON)
            {
                normal = glm::normalize(initialNormal);
            }
            else
            {
                normal = glm::vec3(0.0f, 1.0f, 0.0f);
            }

            // Движемся внутрь поверхности?
            const float velocityIntoSurface =
                glm::dot(displacement, normal);

            if (velocityIntoSurface < -EPSILON)
            {
                hit.hit = true;
                hit.fraction = 0.0f;
                hit.point = initialBoxPoint;
                hit.normal = normal;

                return true;
            }

            // Движемся вдоль поверхности или от неё.
            return false;
        }
    }

    /*
        Check final position.

        If the capsule doesn't intersect at the end and didn't
        intersect at the beginning, there is no collision.
    */
    const glm::vec3 endA =
        capsule.a + displacement;

    const glm::vec3 endB =
        capsule.b + displacement;

    glm::vec3 endSegmentPoint;
    glm::vec3 endBoxPoint;

    const float endDistanceSq =
        segmentAABBDistanceSquared(
            endA,
            endB,
            box,
            endSegmentPoint,
            endBoxPoint);

    if (endDistanceSq > radiusSq)
        return false;

    /*
        The collision function:

            f(t) = distance(segment(t), box)^2 - radius^2

        is <= 0 when the capsule intersects the box.

        Since we know:

            f(0) > 0
            f(1) <= 0

        binary search finds the first collision time.
    */
    float low = 0.0f;
    float high = 1.0f;

    constexpr int BINARY_SEARCH_ITERATIONS = 24;

    for (int i = 0;
         i < BINARY_SEARCH_ITERATIONS;
         ++i)
    {
        const float mid =
            (low + high) * 0.5f;

        const glm::vec3 currentA =
            capsule.a + displacement * mid;

        const glm::vec3 currentB =
            capsule.b + displacement * mid;

        glm::vec3 currentSegmentPoint;
        glm::vec3 currentBoxPoint;

        const float distanceSq =
            segmentAABBDistanceSquared(
                currentA,
                currentB,
                box,
                currentSegmentPoint,
                currentBoxPoint);

        if (distanceSq <= radiusSq)
            high = mid;
        else
            low = mid;
    }

    const float fraction = high;

    const glm::vec3 finalA =
        capsule.a + displacement * fraction;

    const glm::vec3 finalB =
        capsule.b + displacement * fraction;

    glm::vec3 finalSegmentPoint;
    glm::vec3 finalBoxPoint;

    segmentAABBDistanceSquared(
        finalA,
        finalB,
        box,
        finalSegmentPoint,
        finalBoxPoint);

    hit.hit = true;
    hit.fraction = fraction;
    hit.point = finalBoxPoint;

    const glm::vec3 normal =
        finalSegmentPoint -
        finalBoxPoint;

    if (glm::dot(normal, normal) > EPSILON)
    {
        hit.normal =
            glm::normalize(normal);
    }
    else if (
        glm::dot(displacement, displacement) >
        EPSILON)
    {
        hit.normal =
            glm::normalize(-displacement);
    }
    else
    {
        hit.normal =
            glm::vec3(0.0f, 1.0f, 0.0f);
    }

    return true;
}