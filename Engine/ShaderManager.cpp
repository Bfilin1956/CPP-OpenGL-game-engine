#include "ShaderManager.h"


#include <fstream>
#include <ranges>
#include <sstream>

#include "Logger.h"
GLuint ShaderManager::get(const std::string& name) {
    return instance().getImpl(name);
}

ShaderManager::~ShaderManager() {
    for (const auto &shaderProgram: cache | std::views::values) {
        glDeleteProgram(shaderProgram);
    }
    cache.clear();
}

std::string ShaderManager::readFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open())
        Log::print_log("Failed to open: " + path, Log::MsgType::Error);

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

GLuint ShaderManager::compile(const GLenum type, const std::string& src) {
    const GLuint shader = glCreateShader(type);
    const char* cstr = src.c_str();

    glShaderSource(shader, 1, &cstr, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        char log[1024];
        glGetShaderInfoLog(shader, 1024, nullptr, log);
        throw std::runtime_error(log);
    }

    return shader;
}

GLuint ShaderManager::createProgram(const std::string& vs, const std::string& fs) {
    const GLuint v = compile(GL_VERTEX_SHADER, vs);
    const GLuint f = compile(GL_FRAGMENT_SHADER, fs);

    GLuint program = glCreateProgram();
    glAttachShader(program, v);
    glAttachShader(program, f);
    glLinkProgram(program);

    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (!success) {
        char log[1024];
        glGetProgramInfoLog(program, 1024, nullptr, log);
        throw std::runtime_error(log);
    }

    glDeleteShader(v);
    glDeleteShader(f);

    return program;
}

ShaderManager& ShaderManager::instance() {
    static ShaderManager inst;
    return inst;
}

GLuint ShaderManager::getImpl(const std::string& name) {
    if (cache.contains(name))
        return cache[name];

    const std::string vs = readFile("shaders/" + name + ".vert");
    const std::string fs = readFile("shaders/" + name + ".frag");

    const GLuint program = createProgram(vs, fs);

    cache[name] = program;
    return program;
}