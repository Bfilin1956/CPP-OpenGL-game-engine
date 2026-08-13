#pragma once
#include <chrono>

#include "Rendering/Camera.h"
#include "Platform/InputManager.h"
#include "Rendering/Renderer.h"
#include "Scene/RenderObject.h"
#include "Rendering/Shader.h"

#include "Platform/Window.h"
#include "Rendering/Skybox.h"

#include "Scene/Player.h"
#include "Physics/PhysicsWorld.h"
#include "Scene/CharacterController.h"
#include "Scene/PlayerController.h"

#include "Scene/Scene.h"

class Engine{
    static float getDeltaTime();

    void update();
    void render();
public:
    void init();
    static void run();
    Shader* getShader(const std::string& nameShader);
    Scene& getScene();
    void setWindow(Window *window);


    static Engine& instance();
    ~Engine();
    Engine() = default;
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;
    Engine(Engine&&) = delete;
    Engine& operator=(Engine&&) = delete;

private:
    Window *window_{};
    bool running_{true};
    SDL_bool mouseLookEnabled_{SDL_TRUE};
    Renderer *renderer_{};
    InputManager *inputManager_{};

    Scene scene_{};

    Player player_{};
    PlayerController playerController_{};
    CharacterController *characterController_{};
    Camera camera_;
    PhysicsWorld *physicsWorld_{};

    std::unordered_map<std::string, Shader*> shaders_;

    Skybox *skybox_{};
};
