//
// Created by filin on 8/12/26.
//
#include "PlayerController.h"
#include "Platform/InputManager.h"

void PlayerController::setPlayer(Player &playerInput) {
    inputManager_ = &InputManager::instance();
    player_ = &playerInput;
}

void PlayerController::setCamera(Camera &cameraInput) {
    camera_ = &cameraInput;
}

void PlayerController::update(float dt) {
    if (!player_ || !camera_) return;
    PlayerInput input{};

    if (inputManager_->isHeld(SDL_SCANCODE_W)) input.movement.y += 1.0f;
    if (inputManager_->isHeld(SDL_SCANCODE_S)) input.movement.y -= 1.0f;
    if (inputManager_->isHeld(SDL_SCANCODE_D)) input.movement.x += 1.0f;
    if (inputManager_->isHeld(SDL_SCANCODE_A)) input.movement.x -= 1.0f;
    input.jump = inputManager_->isHeld(SDL_SCANCODE_SPACE);
    player_->applyInput(input, camera_->front(), camera_->right());
}
