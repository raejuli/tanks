#ifndef ENGINE_TEXTURE2DCOMPONENT_H
#define ENGINE_TEXTURE2DCOMPONENT_H

#include "component/Component.h"
#include "../texture/Texture2D.h"
#include <string>
#include <memory>

// Component that holds a Texture2D
// Attach this to an entity to provide texture data for renderers
class Texture2DComponent : public Component {
public:
    explicit Texture2DComponent(const std::string& texturePath);
    ~Texture2DComponent() override = default;

    // Get the underlying texture
    Texture2D* getTexture() { return texture.get(); }
    const Texture2D* getTexture() const { return texture.get(); }

    // Check if texture is valid
    bool isValid() const { return texture && texture->isValid(); }

    // Get texture properties
    int getWidth() const { return texture ? texture->getWidth() : 0; }
    int getHeight() const { return texture ? texture->getHeight() : 0; }
    float getAspectRatio() const;

    // Reload texture from a new path
    void setTexturePath(const std::string& path);
    const std::string& getTexturePath() const { return texturePath; }

private:
    std::string texturePath;
    std::unique_ptr<Texture2D> texture;
};

#endif //ENGINE_TEXTURE2DCOMPONENT_H
