#include "FragmentShader.h"
#include <fstream>
#include <sstream>
#include <iostream>

FragmentShader::FragmentShader(const std::string& filePath) : filePath(filePath) {
    std::string source = loadSource(filePath);
    if (!source.empty()) {
        compile(source);
    }
}

FragmentShader::~FragmentShader() {
    if (handle != 0) {
        glDeleteShader(handle);
    }
}

std::string FragmentShader::loadSource(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "ERROR::FRAGMENT_SHADER::FILE_NOT_FOUND: " << path << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void FragmentShader::compile(const std::string& source) {
    handle = glCreateShader(GL_FRAGMENT_SHADER);
    const char* src = source.c_str();
    glShaderSource(handle, 1, &src, nullptr);
    glCompileShader(handle);
    checkCompileErrors();
}

void FragmentShader::checkCompileErrors() {
    GLint success;
    glGetShaderiv(handle, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar infoLog[1024];
        glGetShaderInfoLog(handle, 1024, nullptr, infoLog);
        std::cerr << "ERROR::FRAGMENT_SHADER::COMPILATION_FAILED (" << filePath << ")\n" << infoLog << std::endl;
        valid = false;
    } else {
        valid = true;
    }
}
