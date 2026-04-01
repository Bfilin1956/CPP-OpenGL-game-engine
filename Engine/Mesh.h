#pragma once
#include <span>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Texture.h"

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

class Mesh {
    unsigned int VAO = 0, VBO = 0, EBO = 0;
    GLsizei indexCount = 0;

    void setup();

public:
    std::vector<Vertex> vertices_;
    std::vector<unsigned int> indices_;
    std::vector<Texture> textures_;
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    //~Mesh();
    void draw() const;
};
