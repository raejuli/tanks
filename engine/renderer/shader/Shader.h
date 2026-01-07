#ifndef ENGINE_SHADER_H
#define ENGINE_SHADER_H

#include <string>
#include <memory>
#include <glad/glad.h>
#include "VertexShader.h"
#include "FragmentShader.h"

class Shader {
public:
    // Construct from raw source strings
    Shader(const char* vertexSource, const char* fragmentSource);

    // Construct from VertexShader and FragmentShader objects
    Shader(const VertexShader& vertexShader, const FragmentShader& fragmentShader);

    // Load from .vert and .frag file paths
    static std::unique_ptr<Shader> fromFiles(const std::string& vertexPath, const std::string& fragmentPath);

    ~Shader();

    void use() const;
    GLuint getProgram() const { return program; }
    bool isValid() const { return valid; }

    // Uniform setters
    void setMat4(const std::string& name, const float* value) const;
    void setVec4(const std::string& name, float x, float y, float z, float w) const;
    void setVec3(const std::string& name, float x, float y, float z) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;

private:
    GLuint program = 0;
    bool valid = false;

    void linkProgram(GLuint vertexShader, GLuint fragmentShader);
    GLuint compileShader(GLenum type, const char* source);
    void checkCompileErrors(GLuint shader, const std::string& type);
    void checkLinkErrors(GLuint program);
};

#endif //ENGINE_SHADER_H
