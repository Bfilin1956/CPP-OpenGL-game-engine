#pragma once
#include "Material.h"
#include "Collision.h"
#include "Model.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
struct RenderObject {
    Model* model;

    glm::vec3 position{0};
    glm::vec3 rotation{0};
    glm::vec3 scale{1};


    Material *material;

    glm::mat4 getModelMatrix() const {
        glm::mat4 m(1.0f);
        m = glm::translate(m, position);
        m = glm::scale(m, scale);
        return m;
    }
    AABB aabb{};
};
