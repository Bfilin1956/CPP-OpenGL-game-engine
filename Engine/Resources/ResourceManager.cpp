//
// Created by filin on 8/13/26.
//

#include "ResourceManager.h"

#include "Core/Engine.h"
#include "Resources/ModelLoader.h"

ResourceManager &ResourceManager::instance() {
    static ResourceManager inst;
    return inst;
}

Material *ResourceManager::createMaterial() {

}

void ResourceManager::registerObject(std::string name, glm::vec3 pos = {}) {

    models_.push_back(std::make_unique<Model>(ModelLoader::load(TextureLoader::instance(),name)));
    materials_.push_back(std::make_unique<Material>());

    materials_.back().get()->shader = Engine::instance().getShader("basic");
    materials_.back().get()->color[0] = 1.0f;
    materials_.back().get()->color[1] = 0.0f;
    materials_.back().get()->color[2] = 0.0f;

    RenderObject obj;
    obj.model = models_.back().get();
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
    Engine::instance().getScene().staticObjects.push_back(obj);
}