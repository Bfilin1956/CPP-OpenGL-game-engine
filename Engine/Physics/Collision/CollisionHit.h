#pragma once

#include <glm/vec3.hpp>

struct CollisionHit {
    bool hit = false;

    float fraction = 1.0f;

    glm::vec3 point{};
    glm::vec3 normal{};
};