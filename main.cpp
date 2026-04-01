#include <SDL2/SDL.h>
#include <chrono>

#include "Engine/Engine.h"
#include "Engine/Window.h"

#include "Objects/Cube.h"



int main() {
    bool running = true;
    Window window;
    window.init("Easy", 800, 600);

    Engine engine(window, running);
    engine.init();

    engine.registerObject("assets/platform.obj", {0,-1,0});
    engine.registerObject("assets/roof.obj", {15,1,10});
    engine.registerObject("assets/obj1.obj", {10,1,10});
    engine.registerObject("assets/obj2.obj", {5,2,3});
    engine.registerObject("assets/obj3.obj", {-10,2,3});
    SDL_SetRelativeMouseMode(SDL_TRUE);

    while (running) {
        engine.update();
        engine.render();
    }

    window.shutdown();
    return 0;
}
