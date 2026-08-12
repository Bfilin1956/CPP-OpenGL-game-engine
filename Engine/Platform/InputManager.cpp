#include "InputManager.h"
#include <GL/glew.h>

InputManager &InputManager::instance() {
    static InputManager inst;
    return inst;
}

void InputManager::setWindow(const Window &window) {
    window_ = window;
}

void InputManager::update() {
    mouseDX_ = mouseDY_ = 0;
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
                if (!held_[key]) pressed_[key] = true;
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
                mouseDX_ = static_cast<float>(e.motion.xrel);
                mouseDY_ = static_cast<float>(e.motion.yrel);
            }
            case SDL_WINDOWEVENT: {
                if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
                    glViewport(0, 0, e.window.data1, e.window.data2);
                    window_.setSize(e.window.data1, e.window.data2);
                }
            }
            default: {

            }
        }
    }
}

bool InputManager::isHeld(const SDL_Scancode key) const {
    return get(held_, key);
}

bool InputManager::isPressed(const SDL_Scancode key) const {
    return get(pressed_, key);
}

bool InputManager::isReleased(const SDL_Scancode key) const {
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

bool InputManager::get(const std::unordered_map<SDL_Scancode, bool>& map, const SDL_Scancode key) {
    const auto it = map.find(key);
    return it != map.end() && it->second;
}