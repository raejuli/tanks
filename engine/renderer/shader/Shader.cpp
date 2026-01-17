#include "Shader.h"
#include <iostream>
#include <string>

Shader::Shader(const char* vertexSource, const char* fragmentSource) {
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexSource);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSource);

    linkProgram(vertexShader, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::Shader(const VertexShader& vertexShader, const FragmentShader& fragmentShader) {
    if (!vertexShader.isValid() || !fragmentShader.isValid()) {
        std::cerr << "ERROR::SHADER::INVALID_SHADER_OBJECTS" << std::endl;
        valid = false;
        return;
    }

    linkProgram(vertexShader.getHandle(), fragmentShader.getHandle());
}

// Construct from base path: expects basePath.vert and basePath.frag
Shader::Shader(const std::string& basePath) {
    const std::string vertexPath = basePath + ".vert";
    const std::string fragmentPath = basePath + ".frag";

    VertexShader vertexShader(vertexPath);
    FragmentShader fragmentShader(fragmentPath);

    if (!vertexShader.isValid() || !fragmentShader.isValid()) {
        std::cerr << "ERROR::SHADER::INVALID_SHADER_FILES for base path: " << basePath << std::endl;
        valid = false;
        return;
    }

    linkProgram(vertexShader.getHandle(), fragmentShader.getHandle());
}

std::unique_ptr<Shader> Shader::fromFiles(const std::string& vertexPath, const std::string& fragmentPath) {
    VertexShader vertexShader(vertexPath);
    FragmentShader fragmentShader(fragmentPath);

    if (!vertexShader.isValid() || !fragmentShader.isValid()) {
        return nullptr;
    }

    return std::make_unique<Shader>(vertexShader, fragmentShader);
}

Shader::~Shader() {
    if (program != 0) {
        glDeleteProgram(program);
    }
}

void Shader::linkProgram(GLuint vertexShader, GLuint fragmentShader) {
    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    checkLinkErrors(program);
}

void Shader::use() const {
    glUseProgram(program);
}

void Shader::setMat4(const std::string& name, const float* value) const {
    GLint location = glGetUniformLocation(program, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, value);
}

void Shader::setVec4(const std::string& name, float x, float y, float z, float w) const {
    GLint location = glGetUniformLocation(program, name.c_str());
    glUniform4f(location, x, y, z, w);
}

void Shader::setVec3(const std::string& name, float x, float y, float z) const {
    GLint location = glGetUniformLocation(program, name.c_str());
    glUniform3f(location, x, y, z);
}

void Shader::setInt(const std::string& name, int value) const {
    GLint location = glGetUniformLocation(program, name.c_str());
    glUniform1i(location, value);
}

void Shader::setFloat(const std::string& name, float value) const {
    GLint location = glGetUniformLocation(program, name.c_str());
    glUniform1f(location, value);
}

GLuint Shader::compileShader(GLenum type, const char* source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);
    checkCompileErrors(shader, type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT");
    return shader;
}

void Shader::checkCompileErrors(GLuint shader, const std::string& type) {
    GLint success;
    GLchar infoLog[1024];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::" << type << "::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

void Shader::checkLinkErrors(GLuint prog) {
    GLint success;
    GLchar infoLog[1024];
    glGetProgramiv(prog, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(prog, 1024, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        valid = false;
    } else {
        valid = true;
    }
}
