#pragma once

#include "Scene/Scene.h"
#include "Shapes/Capsule.h"
#include "Collision/CollisionHit.h"

#include "PhysicsWorld.h"

class PhysicsWorld {
public:
    static PhysicsWorld& instance();
    PhysicsWorld() = default;
    PhysicsWorld(const PhysicsWorld&) = delete;
    PhysicsWorld& operator=(const PhysicsWorld&) = delete;
    PhysicsWorld(PhysicsWorld&&) = delete;
    PhysicsWorld& operator=(PhysicsWorld&&) = delete;

    bool sweepCapsule( const Capsule& capsule, const glm::vec3& displacement, CollisionHit& hit) const;
    void setScene(Scene *scene);
private:
    Scene* scene_{};
};