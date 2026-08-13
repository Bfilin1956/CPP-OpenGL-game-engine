#include "Engine.h"

#include <chrono>

#include "Resources/ModelLoader.h"
#include "Rendering/ShaderManager.h"
#include "Resources/Model.h"

void Engine::run() {
    const auto inst = &Engine::instance();
    while (inst->running_) {
        inst->update();
        inst->render();
    }
}

Engine &Engine::instance() {
    static Engine inst;
    return inst;
}

void Engine::setWindow(Window *window) {
    window_ = window;
}

std::chrono::time_point<std::chrono::system_clock> lastTime_ = std::chrono::high_resolution_clock::now();

float Engine::getDeltaTime() {
    const auto now = std::chrono::high_resolution_clock::now();
    const float deltaTime = std::chrono::duration<float>(now - lastTime_).count();
    lastTime_ = now;
    return deltaTime;
}

void Engine::init() {
    renderer_ = &Renderer::instance();
    physicsWorld_ = &PhysicsWorld::instance();
    physicsWorld_->setScene(&scene_);
    characterController_ = new CharacterController(PhysicsWorld::instance());
    auto *shaderPtr = new Shader(ShaderManager::get("skybox"));
    shaders_["skybox"] = shaderPtr;
    shaderPtr = new Shader(ShaderManager::get("basic"));
    shaders_["basic"] = shaderPtr;
    skybox_ = new Skybox(TextureLoader::instance().getSkyboxArray(), *shaders_["skybox"]);

    inputManager_ = &InputManager::instance();
    playerController_.setPlayer(player_);
    playerController_.setCamera(camera_);

    TextureLoader::instance().init();
}

Engine::~Engine() {
    delete characterController_;
    for (const auto& ptr : shaders_) delete ptr.second;
}

Scene &Engine::getScene() {
    return scene_;
}

Shader* Engine::getShader(const std::string& nameShader) {
    const auto it = shaders_.find(nameShader);
    if (it == shaders_.end()) {
        return nullptr;
    }
    return it->second;
}

void Engine::update() {
    auto deltaTime = getDeltaTime();
    inputManager_->update();
    if (inputManager_->isPressed(SDL_SCANCODE_ESCAPE)) {
        running_ = false;
    } else if (inputManager_->isPressed(SDL_SCANCODE_F1)) {
        if (mouseLookEnabled_ == SDL_TRUE) mouseLookEnabled_ = SDL_FALSE;
        else mouseLookEnabled_ = SDL_TRUE;
        SDL_SetRelativeMouseMode(mouseLookEnabled_);
    }
    playerController_.update(deltaTime);
    characterController_->update(player_, deltaTime);
    //camera_.follow(player_.position());
    camera_.update(mouseLookEnabled_, player_);
}

void Engine::render() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 view = camera_.getViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), window_->getAspectRatio(), 0.1f, 100.0f);

    skybox_->draw(camera_, projection);
    renderer_->draw(scene_, view, projection, camera_.position());
    window_->swapBuffers();
}

