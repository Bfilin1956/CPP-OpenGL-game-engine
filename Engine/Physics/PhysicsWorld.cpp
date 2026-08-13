#include "PhysicsWorld.h"

#include "Collision/AABB.h"
#include "Collision/AABBQueries.h"
#include "Collision/CollisionQueries.h"

PhysicsWorld &PhysicsWorld::instance() {
    static PhysicsWorld inst;
    return inst;
}

void PhysicsWorld::setScene(Scene *scene) {
    scene_ = scene;
}

bool PhysicsWorld::sweepCapsule( const Capsule& capsule, const glm::vec3& displacement, CollisionHit& hit) const {
    if (!scene_) return false;

    hit = {};
    bool foundHit = false;
    float closestFraction = 1.0f;

    for (const auto& obj : scene_->staticObjects) {
        const AABB box = getWorldAABB(obj);

        CollisionHit candidate;

        if (!sweepCapsuleVsAABB( capsule, box, displacement, candidate)) {
            continue;
        }

        if (!foundHit || candidate.fraction < closestFraction) {
            foundHit = true;
            closestFraction = candidate.fraction;
            hit = candidate;
        }
    }

    return foundHit;
}