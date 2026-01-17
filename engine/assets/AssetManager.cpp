#include "AssetManager.h"

std::shared_ptr<Texture2D> AssetManager::getTexture(std::string_view id) {
    return textures.get(id);
}

std::shared_ptr<Shader> AssetManager::getShader(std::string_view id) {
    return shaders.get(id);
}
