#pragma once
#include <chrono>

#include "Rendering/Camera.h"
#include "Platform/InputManager.h"
#include "Rendering/Material.h"
#include "Rendering/Mesh.h"
#include "Rendering/Renderer.h"
#include "Scene/RenderObject.h"
#include "Rendering/Shader.h"

#include "Platform/Window.h"
#include "Rendering/Skybox.h"
#include "Rendering/TextureLoader.h"

#include "Scene/Player.h"
#include "../Physics/Collision/CheckCollision.h"
#include "Physics/PhysicsWorld.h"
#include "Resources/ModelLoader.h"
#include "Scene/CharacterController.h"
#include "Scene/PlayerController.h"

#include "Scene/Scene.h"

class Engine{
    static float getDeltaTime();

public:
    explicit Engine(const Window &window, bool &run);
    void init();
    void update();
    void render();
    void registerObject(std::string name, glm::vec3 );

private:
    Window window_;
    bool &running_;
    SDL_bool mouseLookEnabled_{SDL_TRUE};
    Renderer renderer_;
    InputManager *inputManager_{};

    std::vector<std::unique_ptr<Model>> meshes_{};
    std::vector<std::unique_ptr<Material>> materials_;
    Scene scene_;

    Player player_{};
    PlayerController playerController_{};
    CharacterController characterController_;
    Camera camera_;
    PhysicsWorld physicsWorld_;

    Shader shaderSkybox_;
    Shader shaderBasic_;
    TextureLoader textureLoader_;
    ModelLoader modelLoader_{};
    Skybox skybox_;
};
