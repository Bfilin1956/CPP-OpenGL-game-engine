#pragma once

#include "Scene/Scene.h"
#include "Shapes/Capsule.h"
#include "Collision/CollisionHit.h"

#include "PhysicsWorld.h"

class PhysicsWorld {
public:
    explicit PhysicsWorld(Scene& scene);

    bool sweepCapsule( const Capsule& capsule, const glm::vec3& displacement, CollisionHit& hit) const;

private:
    Scene* scene_{};
};