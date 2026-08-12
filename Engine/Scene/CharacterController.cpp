//
// Created by filin on 8/12/26.
//

#include "CharacterController.h"

CharacterController::CharacterController(PhysicsWorld &physics) : physics_(&physics) {}

namespace
{
    glm::vec3 projectOntoPlane(
        const glm::vec3& vector,
        const glm::vec3& normal)
    {
        return vector -
               normal * glm::dot(vector, normal);
    }
}
Capsule CharacterController::makeCapsule(
    const Player& player) const
{
    const glm::vec3 position =
        player.position();

    return {
        position + glm::vec3(
            0.0f,
            radius_,
            0.0f),

        position + glm::vec3(
            0.0f,
            height_ - radius_,
            0.0f),

        radius_
    };
}
void CharacterController::update(
    Player& player,
    float dt)
{
    glm::vec3 velocity = player.velocity();

    velocity.y += gravity_ * dt;

    velocity.x =
        player.moveDirection().x *
        player.speed();

    velocity.z =
        player.moveDirection().z *
        player.speed();

    player.setVelocity(velocity);

    glm::vec3 remaining =
        velocity * dt;

    player.setOnGround(false);

    constexpr int maxIterations = 4;

    for (int iteration = 0;
      iteration < maxIterations;
      ++iteration)
    {
        if (glm::dot(remaining, remaining) < 0.000001f)
            break;

        Capsule capsule = makeCapsule(player);

        CollisionHit hit;

        if (!physics_->sweepCapsule(
                capsule,
                remaining,
                hit))
        {
            player.setPosition(
                player.position() + remaining);

            break;
        }


        const glm::vec3 travel =
            remaining * hit.fraction;

        const glm::vec3 leftover =
            remaining - travel;

        player.setPosition(
            player.position() +
            travel +
            hit.normal * SKIN);

        if (hit.normal.y > 0.7f)
        {
            player.setOnGround(true);

            if (velocity.y < 0.0f)
                velocity.y = 0.0f;
        }
        else if (hit.normal.y < -0.7f)
        {
            if (velocity.y > 0.0f)
                velocity.y = 0.0f;
        }
        else
        {
            velocity =
                projectOntoPlane(
                    velocity,
                    hit.normal);
        }

        remaining =
            projectOntoPlane(
                leftover,
                hit.normal);

        player.setVelocity(velocity);
    }
}