#pragma once
#include <string>
#include <unordered_map>
#include <glm/fwd.hpp>

#include "GL/glew.h"

class Shader {
    int getLocation(const std::string& name);
public:
    Shader(GLuint id);
    void use() const;
    void setMat4(const std::string& name, const float* value);
    void setMat4_mat4(const std::string& name, glm::mat4& value);
    void setVec3(const std::string& name, float x, float y, float z);
    void setInt(const std::string& name, unsigned int x);
    void setFloat(const std::string& name, float x);
private:
    unsigned int id_{};
    std::unordered_map<std::string, int> cache;

};
