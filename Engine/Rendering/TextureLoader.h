#pragma once
#include <array>
#include <string>
#include <unordered_map>
#include <GL/glew.h>

class TextureLoader {
    std::unordered_map<std::string, unsigned int> textures_;
    std::array<std::string, 6> skyboxFaces_{"skybox/left.png", "skybox/right.png", "skybox/up.png", "skybox/down.png", "skybox/front.png", "skybox/back.png"};
public:
    unsigned int getIdTexture(const std::string& nameTexture);
    void init(const std::string &folderPath = "texture");
    std::array<std::string, 6>& getSkyboxArray();

    static TextureLoader& instance();
    TextureLoader() = default;
    TextureLoader(const TextureLoader&) = delete;
    TextureLoader& operator=(const TextureLoader&) = delete;
    TextureLoader(TextureLoader&&) = delete;
    TextureLoader& operator=(TextureLoader&&) = delete;
private:
    static GLuint loadTexture(const std::string& path);
};