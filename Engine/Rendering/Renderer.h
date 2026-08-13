#pragma once
#include <vector>

#include "Scene/Light.h"
#include "Scene/RenderObject.h"
#include "Scene/Scene.h"
#include "TextureLoader.h"
#include "Shader.h"

class Renderer {
public:
    static Renderer& instance();
    Renderer() = default;
    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;
    Renderer(Renderer&&) = delete;
    Renderer& operator=(Renderer&&) = delete;

    static void applyLights(Shader* shader, const std::vector<Light>& lights);
    void buildBatches(std::vector<RenderObject>& objects, std::unordered_map<Shader*, std::vector<RenderObject*>>& batches);
    void draw(Scene &scene, glm::mat4& view, glm::mat4& projection, glm::vec3 viewPos);
    void drawBatches(std::unordered_map<Shader*, std::vector<RenderObject*>>& batches, glm::mat4& view, glm::mat4& projection, glm::vec3 viewPos);
};
