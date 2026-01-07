#include "Texture2DComponent.h"

Texture2DComponent::Texture2DComponent(const std::string& texturePath) 
    : texturePath(texturePath) {
    if (!texturePath.empty()) {
        texture = std::make_unique<Texture2D>(texturePath);
    }
}

float Texture2DComponent::getAspectRatio() const {
    if (!texture || texture->getHeight() == 0) {
        return 1.0f;
    }
    return static_cast<float>(texture->getWidth()) / static_cast<float>(texture->getHeight());
}

void Texture2DComponent::setTexturePath(const std::string& path) {
    texturePath = path;
    if (path.empty()) {
        texture.reset();
    } else {
        texture = std::make_unique<Texture2D>(path);
    }
}
