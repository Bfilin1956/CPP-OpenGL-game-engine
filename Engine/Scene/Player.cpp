//
// Created by filin on 8/12/26.
//

#include "Player.h"

void Player::applyInput(const PlayerInput& input, const glm::vec3& forward, const glm::vec3& right){
    glm::vec3 direction{};

    direction += forward * input.movement.y;
    direction += right * input.movement.x;

    direction.y = 0.0f;

    if (glm::length(direction) > 0.0f)
        direction = glm::normalize(direction);

    moveDir_ = direction;

    if (input.jump )//&& onGround_)
        velocity_.y = jumpSpeed_;
}
const glm::vec3& Player::position() const
{
    return position_;
}

const glm::vec3& Player::velocity() const
{
    return velocity_;
}

const glm::vec3& Player::moveDirection() const
{
    return moveDir_;
}

void Player::setPosition(const glm::vec3& position)
{
    position_ = position;
}

void Player::setVelocity(const glm::vec3& velocity)
{
    velocity_ = velocity;
}

bool Player::onGround() const
{
    return onGround_;
}

void Player::setOnGround(bool value)
{
    onGround_ = value;
}

float Player::speed() const
{
    return speed_;
}

float Player::jumpSpeed() const
{
    return jumpSpeed_;
}