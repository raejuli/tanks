#ifndef ENGINE_FRAGMENTSHADER_H
#define ENGINE_FRAGMENTSHADER_H

#include <string>
#include <glad/glad.h>

class FragmentShader {
public:
    // Load fragment shader from a .frag file
    explicit FragmentShader(const std::string& filePath);
    ~FragmentShader();

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

#endif //ENGINE_FRAGMENTSHADER_H
