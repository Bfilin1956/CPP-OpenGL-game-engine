#include "Engine.h"

#include <chrono>

#include "Resources/ModelLoader.h"
#include "Rendering/ShaderManager.h"
#include "Resources/Model.h"
#include "Resources/ModelLoader.h"

Engine::Engine(const Window &window, bool &run) :
    window_(window),
    running_(run),
    renderer_(textureLoader_),
    physicsWorld_(scene_),
    characterController_(physicsWorld_),
    shaderSkybox_(ShaderManager::get("skybox")),
    shaderBasic_(ShaderManager::get("basic")),
    skybox_(textureLoader_.getSkyboxArray(), shaderSkybox_)
{
    inputManager_ = &InputManager::instance();
    playerController_.setPlayer(player_);
    playerController_.setCamera(camera_);
}

std::chrono::time_point<std::chrono::system_clock> lastTime_ = std::chrono::high_resolution_clock::now();

float Engine::getDeltaTime() {
    const auto now = std::chrono::high_resolution_clock::now();
    const float deltaTime = std::chrono::duration<float>(now - lastTime_).count();
    lastTime_ = now;
    return deltaTime;
}

void Engine::init() {
    textureLoader_.init();
    //ShaderManager::get("basic");
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
    characterController_.update(player_, deltaTime);
    //camera_.follow(player_.position());
    camera_.update(mouseLookEnabled_, player_);
}

void Engine::render() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 view = camera_.getViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), window_.getAspectRatio(), 0.1f, 100.0f);

    skybox_.draw(camera_, projection);
    renderer_.draw(scene_, view, projection, camera_.position());
    window_.swapBuffers();
}

void Engine::registerObject(std::string name, glm::vec3 pos = {}) {

    meshes_.push_back(std::make_unique<Model>(ModelLoader::load(textureLoader_,name)));
    materials_.push_back(std::make_unique<Material>());

    materials_.back().get()->shader = &shaderBasic_;
    materials_.back().get()->color[0] = 1.0f;
    materials_.back().get()->color[1] = 0.0f;
    materials_.back().get()->color[2] = 0.0f;

    RenderObject obj;
    obj.model = meshes_.back().get();
    obj.material = materials_.back().get();
    //obj.model = glm::mat4(1.0f);

    obj.position = pos;

    glm::vec3 min(FLT_MAX), max(-FLT_MAX);

    for (auto& mesh : obj.model->meshes) {
        for (auto& v : mesh.vertices_) {
            min = glm::min(min, v.position);
            max = glm::max(max, v.position);
        }
    }

    obj.aabb.min = min;
    obj.aabb.max = max;
    scene_.staticObjects.push_back(obj);
}

