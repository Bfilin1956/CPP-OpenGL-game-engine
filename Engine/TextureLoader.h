#pragma once
#include <array>
#include <string>
#include <unordered_map>
#include <GL/glew.h>

class TextureLoader {
    std::unordered_map<std::string, unsigned int> textures_;
    std::array<std::string, 6> skyboxFaces_{"texture/skybox/left.png", "texture/skybox/right.png", "texture/skybox/up.png", "texture/skybox/down.png", "texture/skybox/front.png", "texture/skybox/back.png"};

public:
    unsigned int getIdTexture(const std::string& nameTexture);
    void init(const std::string &folderPath = "texture");
    std::array<std::string, 6>& getSkyboxArray();

private:
    static GLuint loadTexture(const std::string& path);
};