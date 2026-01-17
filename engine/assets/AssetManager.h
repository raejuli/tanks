#ifndef ENGINE_ASSETMANAGER_H
#define ENGINE_ASSETMANAGER_H

#include <memory>
#include <string_view>
#include <unordered_map>

#include "AssetCache.h"
#include "renderer/shader/Shader.h"
#include "renderer/texture/Texture2D.h"
#include "service/IService.h"

enum class AssetType {
    Texture, Mesh, Shader, Audio, Animation
};

class AssetManager : public IService {
public:
    AssetManager() : textures(this->idPathMap), shaders(this->idPathMap) { } ;

    void loadSync(std::string_view path, AssetType type, std::string_view id);
    void unloadSync(std::string_view id);

    std::shared_ptr<Texture2D> getTexture(std::string_view id);
    // void getMesh();
    std::shared_ptr<Shader> getShader(std::string_view id);
    // void getAudio();
    // void getAnimation();

    // IService interface
    void update(int dt) override { /* no-op for now */ }

protected:

private:
    AssetCache<Texture2D> textures;
    AssetCache<Shader> shaders;

    std::unordered_map<std::string_view, std::string_view> idPathMap;
};

#endif //ENGINE_ASSETMANAGER_H