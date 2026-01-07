#include "Texture2D.h"
#include <iostream>

// stb_image implementation - only define once in the entire project
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture2D::Texture2D(const std::string& filePath) : filePath(filePath) {
    loadFromFile(filePath);
}

Texture2D::~Texture2D() {
    if (handle != 0) {
        glDeleteTextures(1, &handle);
    }
}

void Texture2D::loadFromFile(const std::string& path) {
    // Flip image vertically (OpenGL expects origin at bottom-left)
    stbi_set_flip_vertically_on_load(true);

    unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
    if (!data) {
        std::cerr << "ERROR::TEXTURE2D::Failed to load texture: " << path << std::endl;
        std::cerr << "  Reason: " << stbi_failure_reason() << std::endl;
        valid = false;
        return;
    }

    // Determine format based on channels
    GLenum internalFormat = GL_RGB;
    GLenum dataFormat = GL_RGB;
    if (channels == 1) {
        internalFormat = GL_RED;
        dataFormat = GL_RED;
    } else if (channels == 3) {
        internalFormat = GL_RGB;
        dataFormat = GL_RGB;
    } else if (channels == 4) {
        internalFormat = GL_RGBA;
        dataFormat = GL_RGBA;
    }

    glGenTextures(1, &handle);
    glBindTexture(GL_TEXTURE_2D, handle);

    // Set default texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Upload texture data
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    // Free image data
    stbi_image_free(data);

    valid = true;
    std::cout << "Loaded texture: " << path << " (" << width << "x" << height << ", " << channels << " channels)" << std::endl;
}

void Texture2D::bind(unsigned int unit) const {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, handle);
}

void Texture2D::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::setWrapMode(TextureWrap wrapS, TextureWrap wrapT) {
    glBindTexture(GL_TEXTURE_2D, handle);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<GLint>(wrapS));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<GLint>(wrapT));
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::setFilterMode(TextureFilter minFilter, TextureFilter magFilter) {
    glBindTexture(GL_TEXTURE_2D, handle);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(minFilter));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(magFilter));
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::generateMipmaps() {
    glBindTexture(GL_TEXTURE_2D, handle);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}
