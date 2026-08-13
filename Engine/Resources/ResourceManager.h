#pragma once
#include "Resources/Model.h"
#include "Rendering/Material.h"
#include "memory"

class ResourceManager {
public:
    Model* loadModel(const std::string& name);
    Material* createMaterial();
    void registerObject(std::string name, glm::vec3);


    static ResourceManager& instance();
    ResourceManager() = default;
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    ResourceManager(ResourceManager&&) = delete;
    ResourceManager& operator=(ResourceManager&&) = delete;
private:
    std::vector<std::unique_ptr<Model>> models_;
    std::vector<std::unique_ptr<Material>> materials_;
};