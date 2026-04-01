#pragma once
#include "RenderObject.h"


struct Player {
    glm::vec3 position {0.0f, 20.0f, 0.0f};
    glm::vec3 velocity{};
    float speed = 5.0f;
    float jumpSpeed = 5.0f;
    float gravity = -9.8f;
    glm::vec3 size = {1.0f, 2.0f, 1.0f};

    bool onGround = false;

    //RenderObject& mesh;
};

