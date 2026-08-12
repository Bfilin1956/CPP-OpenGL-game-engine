//
// Created by filin on 8/12/26.
//

#pragma once

#include <glm/vec3.hpp>

struct Capsule {
    glm::vec3 a;
    glm::vec3 b;
    float radius{0.4f};
};