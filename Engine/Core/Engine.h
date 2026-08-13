#pragma once
#include <chrono>

#include "Rendering/Camera.h"
#include "Platform/InputManager.h"
#include "Rendering/Shader.h"

#include "Platform/Window.h"
#include "Rendering/Skybox.h"

#include "Scene/Player.h"
#include "Scene/CharacterController.h"
#include "Scene/PlayerController.h"

#include "Scene/Scene.h"
class Engine{

    void update();
public:
    void init();
    static void run();
    Shader* getShader(const std::string& nameShader);
    Scene& getScene();


    static Engine& instance();
    Engine() = default;
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;
    Engine(Engine&&) = delete;
    Engine& operator=(Engine&&) = delete;

private:
    bool running_{true};
    SDL_bool mouseLookEnabled_{SDL_TRUE};

    Scene scene_{};
    std::unique_ptr<Skybox> skybox_{};
    Player player_{};
    PlayerController playerController_{};
    std::unique_ptr<CharacterController> characterController_{};
    Camera camera_;

    std::unordered_map<std::string, std::unique_ptr<Shader>> shaders_;
};
