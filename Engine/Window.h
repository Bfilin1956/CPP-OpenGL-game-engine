#pragma once
#include <SDL2/SDL.h>


class Window {
    SDL_Window* window_ = nullptr;
    SDL_GLContext context_ = nullptr;
    int width_ = 800;
    int height_ = 600;
public:
    bool init(const char* title, int width, int height);
    void swapBuffers() const;
    void shutdown() const;
    [[nodiscard]] float getAspectRatio() const;
    void setSize(int w, int h);
    void updateSize();
};