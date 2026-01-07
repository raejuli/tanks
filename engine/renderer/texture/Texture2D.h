#ifndef ENGINE_TEXTURE2D_H
#define ENGINE_TEXTURE2D_H

#include <string>
#include <glad/glad.h>

// Texture wrapping modes
enum class TextureWrap {
    Repeat = GL_REPEAT,
    MirroredRepeat = GL_MIRRORED_REPEAT,
    ClampToEdge = GL_CLAMP_TO_EDGE,
    ClampToBorder = GL_CLAMP_TO_BORDER
};

// Texture filtering modes
enum class TextureFilter {
    Nearest = GL_NEAREST,
    Linear = GL_LINEAR,
    NearestMipmapNearest = GL_NEAREST_MIPMAP_NEAREST,
    LinearMipmapNearest = GL_LINEAR_MIPMAP_NEAREST,
    NearestMipmapLinear = GL_NEAREST_MIPMAP_LINEAR,
    LinearMipmapLinear = GL_LINEAR_MIPMAP_LINEAR
};

// Texture2D class - loads and manages a 2D texture from file
class Texture2D {
public:
    // Load texture from file path
    explicit Texture2D(const std::string& filePath);
    ~Texture2D();

    // Bind texture to a texture unit (default: 0)
    void bind(unsigned int unit = 0) const;
    
    // Unbind texture
    void unbind() const;

    // Getters
    GLuint getHandle() const { return handle; }
    bool isValid() const { return valid; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int getChannels() const { return channels; }
    const std::string& getFilePath() const { return filePath; }

    // Set texture parameters
    void setWrapMode(TextureWrap wrapS, TextureWrap wrapT);
    void setFilterMode(TextureFilter minFilter, TextureFilter magFilter);

    // Generate mipmaps (call after loading if using mipmap filters)
    void generateMipmaps();

private:
    GLuint handle = 0;
    bool valid = false;
    int width = 0;
    int height = 0;
    int channels = 0;
    std::string filePath;

    void loadFromFile(const std::string& path);
};

#endif //ENGINE_TEXTURE2D_H
