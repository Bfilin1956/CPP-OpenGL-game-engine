#include <SDL2/SDL.h>
#include <chrono>

#include "Engine/Core/Engine.h"
#include "Engine/Platform/Window.h"

#include "Resources/ResourceManager.h"


int main() {

    Window::instance().init("Easy", 1280, 720);

    Engine::instance().init();

    ResourceManager::instance().registerObject("assets/platform.obj", {0,-1,0});
    ResourceManager::instance().registerObject("assets/roof.obj", {15,1,10});
    ResourceManager::instance().registerObject("assets/obj3.obj", {-10,2,3});
    SDL_SetRelativeMouseMode(SDL_TRUE);

    Engine::run();

    Window::instance().shutdown();
    return 0;
}
