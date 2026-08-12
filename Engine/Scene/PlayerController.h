#pragma once
#include "Player.h"

class PlayerController {
public:
    void setPlayer(Player &playerInput);
    void setCamera(Camera &cameraInput);
    void update(float dt);
private:
    Player *player_{};
    Camera *camera_{};
    InputManager *inputManager_{};
};