#include "TextureLoader.h"
#include <filesystem>
#include <stb_image.h>

#include "Logger.h"

namespace fs = std::filesystem;

unsigned int TextureLoader::getIdTexture(const std::string& nameTexture) {
    if (textures_.contains(nameTexture))
        return textures_[nameTexture];
    return 0;
}

void TextureLoader::init(const std::string &folderPath) {

    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (!entry.is_regular_file()) continue;
        if (const auto& path = entry.path(); path.extension() == ".png") {
            const GLuint texID = loadTexture(path.string());

            std::string name = path.stem().string();
            name += ".png";
            std::cout << name << std::endl;
            textures_[name] = texID;
        }
    }
}

std::array<std::string, 6>& TextureLoader::getSkyboxArray() {
    return skyboxFaces_;
}

GLuint TextureLoader::loadTexture(const std::string& path) {
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    stbi_set_flip_vertically_on_load(true);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    int width, height, channels;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

    if (data) {
        GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;

        glTexImage2D(GL_TEXTURE_2D, 0, format,
                     width, height, 0,
                     format, GL_UNSIGNED_BYTE, data);

        glGenerateMipmap(GL_TEXTURE_2D);

        // wrapping
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // filtering
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // anisotropic filtering
        if (GLEW_EXT_texture_filter_anisotropic) {
            float maxAniso = 0.0f;
            glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAniso);
            glTexParameterf(GL_TEXTURE_2D,
                GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAniso);
        }

    } else {
        Log::print_log("Failed to load texture: " + path, Log::MsgType::Error);
    }

    stbi_image_free(data);
    return textureID;
}