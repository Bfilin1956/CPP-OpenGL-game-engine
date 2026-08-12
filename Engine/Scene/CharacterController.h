//
// Created by filin on 8/12/26.
//
#pragma once
#include "Physics/PhysicsWorld.h"
#include "Scene/Player.h"
class CharacterController {
public:
    explicit CharacterController(PhysicsWorld& physics);

    Capsule makeCapsule( const Player& player) const;

    void update(Player& player, float dt);

private:
    PhysicsWorld* physics_{};
    float SKIN = 0.001f;

    float gravity_ = -9.8f;

    float radius_ = 0.4f;
    float height_ = 1.8f;
};