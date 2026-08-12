#pragma once
#include <string>

struct Texture {
    std::string type; // diffuse, specular, etc
    std::string path; // путь в ассетах
    unsigned int id;        // gl texture id
};
