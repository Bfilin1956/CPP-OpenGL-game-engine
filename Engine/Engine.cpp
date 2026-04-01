#include "Engine.h"

#include <chrono>

#include "ModelLoader.h"
#include "ShaderManager.h"

Engine::Engine(const Window &window, bool &run) :
    window_(window),
    running_(run),
    renderer_(textureLoader_),
    inputManager_(window_),
    camera_(inputManager_, player_),
    shaderBasic_(ShaderManager::get("basic")),
    shaderSkybox_(ShaderManager::get("skybox")),
    skybox_(textureLoader_.getSkyboxArray(), shaderSkybox_) {
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
    inputManager_.update();
    if (inputManager_.isPressed(SDL_SCANCODE_ESCAPE)) {
        running_ = false;
    }else if (inputManager_.isPressed(SDL_SCANCODE_F1)) {
        if (is_f1_ == SDL_TRUE) is_f1_ = SDL_FALSE;
        else is_f1_ = SDL_TRUE;
        SDL_SetRelativeMouseMode(is_f1_);
    }
    updatePlayer(player_, deltaTime, scene_);

    camera_.update(deltaTime, is_f1_);
}

void Engine::render() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 view = camera_.getViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), window_.getAspectRatio(), 0.1f, 100.0f);

    skybox_.draw(camera_, projection);
    renderer_.draw(scene_, view, projection, camera_.Position);
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
bool isStandingOn(const AABB& player, const AABB& obj) {
    float epsilon = 0.05f;

    return
        player.min.y >= obj.max.y - epsilon &&
        player.min.y <= obj.max.y + epsilon;
}
void Engine::updatePlayer(Player& player, float dt, Scene& scene) const {

    // ----------- INPUT -----------
    glm::vec3 moveDir{};

    if (inputManager_.isHeld(SDL_SCANCODE_W)) moveDir += camera_.Front;
    if (inputManager_.isHeld(SDL_SCANCODE_S)) moveDir -= camera_.Front;
    if (inputManager_.isHeld(SDL_SCANCODE_A)) moveDir -= camera_.Right;
    if (inputManager_.isHeld(SDL_SCANCODE_D)) moveDir += camera_.Right;

    moveDir.y = 0.0f;
    if (glm::length(moveDir) > 0.0f)
        moveDir = glm::normalize(moveDir);

    player.velocity.x = moveDir.x * player.speed;
    player.velocity.z = moveDir.z * player.speed;

    // ----------- JUMP -----------
    if (inputManager_.isHeld(SDL_SCANCODE_SPACE) && player.onGround) {
        player.velocity.y = player.jumpSpeed;
        player.onGround = false;
    }
    if (inputManager_.isHeld(SDL_SCANCODE_C) && player.onGround) {
        player.velocity.y = -player.jumpSpeed;
    }

    // ----------- GRAVITY -----------
    player.velocity.y += player.gravity * dt;

    // ----------- X AXIS -----------
    player.position.x += player.velocity.x * dt;

    {
        AABB playerBox = {
            player.position - player.size * 0.5f,
            player.position + player.size * 0.5f
        };

        for (auto& obj : scene.staticObjects) {
            AABB objBox = getAABB(obj);

            if (checkCollision(playerBox, objBox)) {

                // если стоим сверху → НЕ трогаем X
                if (isStandingOn(playerBox, objBox))
                    continue;

                if (player.velocity.x > 0)
                    player.position.x = objBox.min.x - player.size.x * 0.5f;
                else if (player.velocity.x < 0)
                    player.position.x = objBox.max.x + player.size.x * 0.5f;
            }
        }
    }

    // ----------- Z AXIS -----------
    player.position.z += player.velocity.z * dt;

    {
        AABB playerBox = {
            player.position - player.size * 0.5f,
            player.position + player.size * 0.5f
        };

        for (auto& obj : scene.staticObjects) {
            AABB objBox = getAABB(obj);

            if (checkCollision(playerBox, objBox)) {
                if (isStandingOn(playerBox, objBox))
                    continue;

                if (player.velocity.z > 0)
                    player.position.z = objBox.min.z - player.size.z * 0.5f;
                else if (player.velocity.z < 0)
                    player.position.z = objBox.max.z + player.size.z * 0.5f;
            }
        }
    }

    // ----------- Y AXIS (ГРАВИТАЦИЯ) -----------
    player.position.y += player.velocity.y * dt;

    player.onGround = 1;

    {
        AABB playerBox = {
            player.position - player.size * 0.5f,
            player.position + player.size * 0.5f
        };

        for (auto& obj : scene.staticObjects) {
            AABB objBox = getAABB(obj);

            if (checkCollision(playerBox, objBox)) {

                // падение вниз
                if (player.velocity.y < 0) {
                    player.position.y = objBox.max.y + player.size.y * 0.5f;
                    player.velocity.y = 0;
                    player.onGround = true;
                }
                // удар головой
                else if (player.velocity.y > 0) {
                    player.position.y = objBox.min.y - player.size.y * 0.5f;
                    player.velocity.y = 0;
                }
            }
        }
    }
}
