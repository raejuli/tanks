#ifndef ENGINE_VERTEXSHADER_H
#define ENGINE_VERTEXSHADER_H

#include <string>
#include <glad/glad.h>

class VertexShader {
public:
    // Load vertex shader from a .vert file
    explicit VertexShader(const std::string& filePath);
    ~VertexShader();

    GLuint getHandle() const { return handle; }
    bool isValid() const { return valid; }
    const std::string& getFilePath() const { return filePath; }

private:
    GLuint handle = 0;
    bool valid = false;
    std::string filePath;

    std::string loadSource(const std::string& path);
    void compile(const std::string& source);
    void checkCompileErrors();
};

#endif //ENGINE_VERTEXSHADER_H
