#pragma once
#include <unordered_map>
#include "Window.h"

class InputManager {
    static bool get(const std::unordered_map<SDL_Scancode, bool>& map, SDL_Scancode key);
public:
    static InputManager& instance();
    InputManager() = default;
    InputManager(const InputManager&) = delete;
    InputManager& operator=(const InputManager&) = delete;
    InputManager(InputManager&&) = delete;
    InputManager& operator=(InputManager&&) = delete;

    void setWindow(const Window &window);
    void update();
    bool isHeld(SDL_Scancode key) const;
    bool isPressed(SDL_Scancode key) const;
    bool isReleased(SDL_Scancode key) const;
    bool quitRequested() const;
    float& getMouseDX();
    float& getMouseDY();

private:
    Window window_{};

    float mouseDX_{};
    float mouseDY_{};

    std::unordered_map<SDL_Scancode, bool> held_;
    std::unordered_map<SDL_Scancode, bool> pressed_;
    std::unordered_map<SDL_Scancode, bool> released_;

    bool quit_ = false;
};
