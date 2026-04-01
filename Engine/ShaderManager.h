#pragma once
#include <string>
#include <unordered_map>
#include <GL/glew.h>

class ShaderManager {
public:
    static GLuint get(const std::string& name);
    ~ShaderManager();

private:
    std::unordered_map<std::string, GLuint> cache;

private:
    static std::string readFile(const std::string& path);

    static GLuint compile(GLenum type, const std::string& src);

    static GLuint createProgram(const std::string& vs, const std::string& fs);
    static ShaderManager& instance();
    GLuint getImpl(const std::string& name);
};