#pragma once

#include <span>
#include <string>

#include "Shader.h"
#include "Camera.h"


/*#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"*/

class Skybox {
    unsigned int cubeMapTexture_{};
    unsigned int VAO_{}, VBO_{};
    Shader &shader_;
public:
    Skybox(std::span<std::string> faces, Shader& shader);
    void draw(const Camera& camera, glm::mat4& projection) const;
    void setNumberShader(unsigned int);
private:
    void setupMesh();

    static unsigned int loadCubeMap(std::span<std::string> faces);
};