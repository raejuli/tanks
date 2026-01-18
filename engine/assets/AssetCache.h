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

    void load(std::string_view id) {
        auto it = assets.find(id);
        if (it != assets.end() && !it->second.expired()) {
            return;  // Already loaded
        }

        auto pathIt = idPathMap.find(id);
        std::shared_ptr<T> asset = std::make_shared<T>(pathIt->second.data());
        assets[id] = asset;
        pending[id] = asset;
    }

    void unload(std::string_view id) {
        pending.erase(id);
        assets.erase(id);
    }

    std::shared_ptr<T> get(std::string_view id) {
        if (auto it = assets.find(id); it !=assets.end()) {
            if (auto asset = it->second.lock()) {
                pending.erase(id);

                return asset;
            }
        }

        pending.erase(id);

        // asset is not in cache so reload it
        if (auto it = idPathMap.find(id); it != idPathMap.end()) {
            std::shared_ptr<T> asset = std::make_shared<T>(it->second.data());
            assets.insert(std::make_pair(id, asset));

            return asset;
        }

        return nullptr;
    }

private:
    std::unordered_map<std::string_view, std::shared_ptr<T>> pending;
    std::unordered_map<std::string_view, std::string_view> idPathMap;
    // asset id -> T (the asset)
    std::unordered_map<std::string_view, std::weak_ptr<T>> assets;
};


#endif //ENGINE_ASSETCACHE_H