#include "InputManager.h"

#include <GL/glew.h>

InputManager::InputManager(Window &window) : window_(window), mouseDX_(0), mouseDY_(0) {
}

void InputManager::update() {

        mouseDX_ = 0;
        mouseDY_ = 0;
        pressed_.clear();
        released_.clear();

        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT: {
                    quit_ = true;
                    break;
                }
                case SDL_KEYDOWN: {
                    SDL_Scancode key = e.key.keysym.scancode;

                    if (!held_[key])
                        pressed_[key] = true;

                    held_[key] = true;
                    break;
                }
                case SDL_KEYUP: {
                    SDL_Scancode key = e.key.keysym.scancode;

                    held_[key] = false;
                    released_[key] = true;
                    break;
                }
                case SDL_MOUSEMOTION: {
                    mouseDX_ = e.motion.xrel;
                    mouseDY_ = e.motion.yrel;
                }
                case SDL_WINDOWEVENT: {
                    if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
                        glViewport(0, 0, e.window.data1, e.window.data2);
                        window_.setSize(e.window.data1, e.window.data2);
                    }
                }
            }
        }
    }

bool InputManager::isHeld(SDL_Scancode key) const {
    return get(held_, key);
}

bool InputManager::isPressed(SDL_Scancode key) const {
    return get(pressed_, key);
}

bool InputManager::isReleased(SDL_Scancode key) const {
    return get(released_, key);
}

bool InputManager::quitRequested() const {
    return quit_;
}

float& InputManager::getMouseDX() {
    return mouseDX_;
}

float& InputManager::getMouseDY() {
    return mouseDY_;
}

bool InputManager::get(const std::unordered_map<SDL_Scancode, bool>& map,
            SDL_Scancode key) {
    auto it = map.find(key);
    return it != map.end() && it->second;
}