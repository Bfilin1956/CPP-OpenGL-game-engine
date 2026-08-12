#pragma once
#include "glm/vec2.hpp"

struct PlayerInput {
    glm::vec2 movement{};
    bool jump = false;
};
