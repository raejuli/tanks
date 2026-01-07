#include "VertexShader.h"
#include <fstream>
#include <sstream>
#include <iostream>

VertexShader::VertexShader(const std::string& filePath) : filePath(filePath) {
    std::string source = loadSource(filePath);
    if (!source.empty()) {
        compile(source);
    }
}

VertexShader::~VertexShader() {
    if (handle != 0) {
        glDeleteShader(handle);
    }
}

std::string VertexShader::loadSource(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "ERROR::VERTEX_SHADER::FILE_NOT_FOUND: " << path << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void VertexShader::compile(const std::string& source) {
    handle = glCreateShader(GL_VERTEX_SHADER);
    const char* src = source.c_str();
    glShaderSource(handle, 1, &src, nullptr);
    glCompileShader(handle);
    checkCompileErrors();
}

void VertexShader::checkCompileErrors() {
    GLint success;
    glGetShaderiv(handle, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar infoLog[1024];
        glGetShaderInfoLog(handle, 1024, nullptr, infoLog);
        std::cerr << "ERROR::VERTEX_SHADER::COMPILATION_FAILED (" << filePath << ")\n" << infoLog << std::endl;
        valid = false;
    } else {
        valid = true;
    }
}
