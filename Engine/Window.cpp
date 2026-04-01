#include "Window.h"

#include <GL/glew.h>

#include "Logger.h"

bool Window::init(const char* title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        std::string error = "SDL Init Failed: ";
        error += SDL_GetError();
        Log::print_log(error, Log::MsgType::Error);
        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    window_ = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
                               | SDL_WINDOW_RESIZABLE);
    if (!window_) {
        std::string error = "Window creation failed: ";
        error += SDL_GetError();
        Log::print_log(error, Log::MsgType::Error);
        return false;
    }

    context_ = SDL_GL_CreateContext(window_);
    if (!context_) {
        std::string error = "OpenGL context creation failed: ";
        error += SDL_GetError();
        Log::print_log(error, Log::MsgType::Error);
        return false;
    }

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        Log::print_log("GLEW init failed", Log::MsgType::Error);
        return false;
    }

    glEnable(GL_DEPTH_TEST);
    return true;
}

void Window::swapBuffers() const {
    SDL_GL_SwapWindow(window_);
}

void Window::shutdown() const {
    if (context_) SDL_GL_DeleteContext(context_);
    if (window_) SDL_DestroyWindow(window_);
    SDL_Quit();
}

float Window::getAspectRatio() const {
    return static_cast<float>(width_) / static_cast<float>(height_);
}

void Window::setSize(const int w, const int h) {
    width_ = w;
    height_ = h;
}

void Window::updateSize() {
    SDL_GetWindowSize(window_, &width_, &height_);
}