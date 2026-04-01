#pragma once
#include <vector>

#include "Light.h"
#include "RenderObject.h"
#include "Scene.h"
#include "TextureLoader.h"

class Renderer {
    TextureLoader &textureLoader_;

public:
    explicit Renderer(TextureLoader &textureLoader);

    static void applyLights(Shader* shader, const std::vector<Light>& lights);
    void buildBatches(std::vector<RenderObject>& objects, std::unordered_map<Shader*, std::vector<RenderObject*>>& batches);
    void draw(Scene &scene, glm::mat4& view, glm::mat4& projection, glm::vec3 viewPos);
    void drawBatches(std::unordered_map<Shader*, std::vector<RenderObject*>>& batches, glm::mat4& view, glm::mat4& projection, glm::vec3 viewPos);
};
