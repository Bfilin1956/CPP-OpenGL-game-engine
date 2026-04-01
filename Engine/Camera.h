#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "InputManager.h"
#include "Player.h"

struct Camera {
    InputManager &input;
    glm::vec3 Position{};

    float Yaw = -90.0f;
    float Pitch = 0.0f;
    float Sensitivity = 0.5f;

    glm::vec3 Front{0,0,-1};
    glm::vec3 Up{0,1,0};
    glm::vec3 Right{1,0,0};

    Player &player;
    float heightOffset = 1.8f;

    Camera(InputManager &input_manager, Player& p);

    [[nodiscard]] glm::mat4 getViewMatrix() const;

    void update(float deltaTime, SDL_bool is_f1);

private:
    void updateVectors();
};
