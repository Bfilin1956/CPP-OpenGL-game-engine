#pragma once
#include "PlayerInput.h"
#include "Rendering/Camera.h"

class Player {
public:
    void applyInput(const PlayerInput& input, const glm::vec3& forward, const glm::vec3& right);
    const glm::vec3& position() const;
    const glm::vec3& velocity() const;
    const glm::vec3& moveDirection() const;

    void setPosition(const glm::vec3& position);
    void setVelocity(const glm::vec3& velocity);

    bool onGround() const;
    void setOnGround(bool value);

    float speed() const;
    float jumpSpeed() const;
private:
    glm::vec3 moveDir_{};
    glm::vec3 position_{0.0f, 20.0f, 0.0f};
    glm::vec3 velocity_{};

    float speed_ = 5.0f;
    float jumpSpeed_ = 5.0f;

    bool onGround_ = false;
};