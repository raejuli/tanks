#ifndef ENGINE_ASSETCACHE_H
#define ENGINE_ASSETCACHE_H

#include <memory>
#include <unordered_map>

template<typename T>
class AssetCache {
public:
    explicit AssetCache(std::unordered_map<std::string_view, std::string_view>& idPathMap) {
        this->idPathMap = idPathMap;
    }

    std::shared_ptr<T> get(std::string_view id) {
        if (auto it = assets.find(id); it !=assets.end()) {
            if (auto asset = it->second.lock()) {
                return asset;
            }
        }

        // asset is not in cache so reload it
        if (auto it = idPathMap.find(id); it != idPathMap.end()) {
            std::shared_ptr<T> asset = std::make_shared<T>(it->second.data());
            assets.insert(std::make_pair(id, asset));

            return asset;
        }

        return nullptr;
    }

private:
    std::unordered_map<std::string_view, std::string_view> idPathMap;
    // asset id -> T (the asset)
    std::unordered_map<std::string_view, std::weak_ptr<T>> assets;
};


#endif //ENGINE_ASSETCACHE_H