#include "Engine.h"

#include <chrono>

#include "Resources/ModelLoader.h"
#include "Rendering/ShaderManager.h"
#include "Time.h"
#include "Rendering/RenderSystem.h"

void Engine::run() {
    Engine& engine = instance();
    while (engine.running_) {
        engine.update();
        RenderSystem::instance().render( engine.scene_, engine.camera_);
    }
}

Engine &Engine::instance() {
    static Engine inst;
    return inst;
}

void Engine::init() {
    PhysicsWorld::instance().setScene(&scene_);
    characterController_ = std::make_unique<CharacterController>(PhysicsWorld::instance());
    shaders_["skybox"] = std::make_unique<Shader>(ShaderManager::get("skybox"));
    shaders_["basic"] = std::make_unique<Shader>(ShaderManager::get("basic"));
    skybox_ = std::make_unique<Skybox>(TextureLoader::instance().getSkyboxArray(), *shaders_["skybox"]);
    RenderSystem::instance().setSkyBox(skybox_.get());

    playerController_.setPlayer(player_);
    playerController_.setCamera(camera_);

    TextureLoader::instance().init("texture");
}

Scene &Engine::getScene() {
    return scene_;
}

Shader* Engine::getShader(const std::string& nameShader) {
    const auto it = shaders_.find(nameShader);
    if (it == shaders_.end()) {
        return nullptr;
    }
    return it->second.get();
}

void Engine::update() {
    Time::instance().update();
    auto deltaTime = Time::instance().deltaTime();
    auto &inputManager = InputManager::instance();
    inputManager.update();
    if (inputManager.isPressed(SDL_SCANCODE_ESCAPE)) {
        running_ = false;
    } else if (inputManager.isPressed(SDL_SCANCODE_F1)) {
        if (mouseLookEnabled_ == SDL_TRUE) mouseLookEnabled_ = SDL_FALSE;
        else mouseLookEnabled_ = SDL_TRUE;
        SDL_SetRelativeMouseMode(mouseLookEnabled_);
    }
    playerController_.update(deltaTime);
    characterController_->update(player_, deltaTime);
    //camera_.follow(player_.position());
    camera_.update(mouseLookEnabled_, player_);
}

