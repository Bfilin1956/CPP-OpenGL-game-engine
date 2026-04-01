#pragma once
#include "Shader.h"
#include "Texture.h"

struct Material {
    Shader* shader;
    glm::vec3 color{1.0f, 1.0f, 1.0f};

    std::vector<Texture> textures;


    void apply() const {
        shader->use();
        shader->setVec3("uColor", color[0], color[1], color[2]);
    }
};
