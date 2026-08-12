#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/InputManager.h"
#include "Scene/Player.h"

Camera::Camera() {
    inputManager_ = &InputManager::instance();
    updateVectors();
}

const glm::vec3& Camera::front() const {
    return front_;
}

const glm::vec3& Camera::right() const {
    return right_;
}
const glm::vec3& Camera::position() const {
    return position_;
}


glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt( position_, position_ + front_, up_ );
}

void Camera::update(bool mouseLookEnabled, Player& player) {
    //rotation += mouseDelta * sensitivity * dt;

    position_ = player.position() + glm::vec3(0.0f, eyeHeight_, 0.0f);

    if (mouseLookEnabled) {
        const float xOffset = inputManager_->getMouseDX() * sensitivity_;
        const float yOffset = -inputManager_->getMouseDY() * sensitivity_;
        yaw_ += xOffset;
        pitch_ += yOffset;
        pitch_ = glm::clamp(pitch_, -89.0f, 89.0f);
    }

    updateVectors();
}

void Camera::updateVectors() {
    const float yaw = glm::radians(yaw_);
    const float pitch = glm::radians(pitch_);

    glm::vec3 front;
    front.x = cos(yaw) * cos(pitch);
    front.y = sin(pitch);
    front.z = sin(yaw) * cos(pitch);
    front_ = glm::normalize(front);
    right_ = glm::normalize( glm::cross(front_, glm::vec3(0.0f, 1.0f, 0.0f)) );
    up_ = glm::normalize( glm::cross(right_, front_) );
}
