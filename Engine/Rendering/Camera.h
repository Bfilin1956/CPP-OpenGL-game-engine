#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class InputManager;
class Player;

class Camera {
public:
    Camera();
    void update(bool mouseLookEnabled, Player& player);
    [[nodiscard]] glm::mat4 getViewMatrix() const;
    [[nodiscard]] const glm::vec3& front() const;
    [[nodiscard]] const glm::vec3& right() const;
    [[nodiscard]] const glm::vec3& position() const;
private:
    void updateVectors();

private:
    InputManager* inputManager_{};
    glm::vec3 position_{};

    float yaw_ = -90.0f;
    float pitch_ = 0.0f;
    float sensitivity_ = 0.5f;

    glm::vec3 front_{0.0f, 0.0f, -1.0f};
    glm::vec3 up_{0.0f, 1.0f, 0.0f};
    glm::vec3 right_{1.0f, 0.0f, 0.0f};

    float eyeHeight_ = 1.6f;
};