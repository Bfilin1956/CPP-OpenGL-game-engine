#pragma once
#include <chrono>

#include "Camera.h"
#include "InputManager.h"
#include "Material.h"
#include "Mesh.h"
#include "Renderer.h"
#include "RenderObject.h"
#include "Shader.h"

#include "Window.h"
#include "Skybox.h"
#include "TextureLoader.h"

#include "Player.h"
#include "Collision.h"
#include "ModelLoader.h"

#include "Scene.h"


inline AABB getAABB(const RenderObject& obj) {
    /*return {obj.position - glm::vec3(0.5f), obj.position + glm::vec3(0.5f)};*/
    glm::vec3 scaledMin = obj.aabb.min * obj.scale;
    glm::vec3 scaledMax = obj.aabb.max * obj.scale;

    glm::vec3 worldMin = obj.position + scaledMin;
    glm::vec3 worldMax = obj.position + scaledMax;

    return {worldMin, worldMax};
}

class Engine{
    Window window_;
    bool &running_;
    SDL_bool is_f1_{SDL_TRUE};
    Renderer renderer_;
    InputManager inputManager_;
    Camera camera_;
    std::vector<std::unique_ptr<Model>> meshes_;
    std::vector<std::unique_ptr<Material>> materials_;
    Scene scene_;
    Player player_;

    Shader shaderSkybox_;
    Shader shaderBasic_;
    TextureLoader textureLoader_;
    ModelLoader modelLoader_;
    Skybox skybox_;
private:
    static float getDeltaTime();

public:
    explicit Engine(const Window &window, bool &run);
    void init();
    void update();
    void render();
    void registerObject(std::string name, glm::vec3 ) ;
    void updatePlayer(Player& player, float deltaTime, Scene &scene) const;
};
