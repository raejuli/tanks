#include "AssetManager.h"

void AssetManager::loadSync(std::string_view path, AssetType type, std::string_view id) {
    switch (type) {
        case AssetType::Texture:
            textures.load(id);
            return;
        case AssetType::Shader:
            shaders.load(id);
    }
}

void AssetManager::unloadSync(AssetType type, std::string_view id) {
    switch (type) {
        case AssetType::Texture:
            textures.unload(id);
            return;
        case AssetType::Shader:
            shaders.unload(id);
    }
}

std::shared_ptr<Texture2D> AssetManager::getTexture(std::string_view id) {
    return textures.get(id);
}

std::shared_ptr<Shader> AssetManager::getShader(std::string_view id) {
    return shaders.get(id);
}
