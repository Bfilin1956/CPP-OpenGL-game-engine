#include "Shader.h"

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const unsigned int id) : id_(id){}

void Shader::use() const {
    glUseProgram(id_);
}

void Shader::setMat4(const std::string& name, const float* value) {
    int loc = getLocation(name);
    glUniformMatrix4fv(loc, 1, GL_FALSE, value);
}

void Shader::setMat4_mat4(const std::string& name, glm::mat4& value) {
    int loc = getLocation(name);
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setVec3(const std::string& name, float x, float y, float z) {
    int loc = getLocation(name);
    glUniform3f(loc, x, y, z);
}

void Shader::setFloat(const std::string& name, float x) {
    int loc = getLocation(name);
    glUniform1f(loc, x);
}

void Shader::setInt(const std::string& name, unsigned int x) {
    int loc = getLocation(name);
    glUniform1i(loc, x);
}

int Shader::getLocation(const std::string& name) {
    if (cache.contains(name))
        return cache[name];

    int loc = glGetUniformLocation(id_, name.c_str());
    cache[name] = loc;
    return loc;
}
