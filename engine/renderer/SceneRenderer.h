#ifndef ENGINE_SCENERENDERER_H
#define ENGINE_SCENERENDERER_H

#include "Camera.h"
#include "shader/Shader.h"
#include "scene/SceneTree.h"
#include "entity/Entity.h"
#include <memory>
#include <string>

// Forward declaration
class RendererComponent;

// SceneRenderer traverses a scene tree and renders all entities with renderer components
class SceneRenderer {
public:
    // Constructor takes path to shaders directory (e.g., "shaders/")
    explicit SceneRenderer(const std::string& shaderPath = "shaders/");
    ~SceneRenderer();

    // Initialize the renderer (loads shaders, etc.)
    void initialize();
    
    // Set the camera used for rendering
    void setCamera(Camera* camera);
    
    // Render the entire scene tree
    void render(SceneTree* root);
    
    // Clear the screen with a colour
    void clear(float r = 0.1f, float g = 0.1f, float b = 0.1f, float a = 1.0f);

    // Get the shader
    Shader* getShader() { return shader.get(); }

    // Set shader directory path
    void setShaderPath(const std::string& path) { shaderPath = path; }

private:
    Camera* camera = nullptr;
    std::unique_ptr<Shader> shader;
    std::string shaderPath;
    bool initialized = false;

    // Helper to build model matrix from transform
    void buildModelMatrix(const class TransformComponent& transform, float* outMatrix);
    
    // Render a single entity
    void renderEntity(Entity* entity);
};

#endif //ENGINE_SCENERENDERER_H
