#include "SceneRenderer.h"
#include "components/RendererComponent.h"
#include "transform/TransformComponent.h"
#include <glad/glad.h>
#include <queue>
#include <cstring>
#include <iostream>

SceneRenderer::SceneRenderer(const std::string& shaderPath) : shaderPath(shaderPath) {}

SceneRenderer::~SceneRenderer() = default;

void SceneRenderer::initialize() {
    if (initialized) return;
    
    // Load shader (supports both solid colour and textured rendering)
    shader = Shader::fromFiles(shaderPath + "scene.vert", shaderPath + "scene.frag");
    if (!shader || !shader->isValid()) {
        std::cerr << "ERROR::SCENE_RENDERER::Failed to load shaders from: " << shaderPath << std::endl;
        return;
    }
    
    initialized = true;
}

void SceneRenderer::setCamera(Camera* cam) {
    camera = cam;
}

void SceneRenderer::clear(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void SceneRenderer::render(SceneTree* root) {
    if (!initialized || !camera || !root || !shader) return;

    // Set up shader with camera matrices
    shader->use();
    shader->setMat4("viewProjection", camera->getViewProjectionMatrix());

    Tree::Traverse<SceneTree>(root, [this](SceneTree* node) {
        if (auto* sceneNode = dynamic_cast<Entity*>(node)) {
            renderEntity(sceneNode);
        }
    });
}

void SceneRenderer::renderEntity(Entity* entity) {
    if (!entity) return;

    // Get the transform component
    TransformComponent* transform = entity->getComponent<TransformComponent>("transform");
    if (!transform) return;

    // Get the renderer component (if any)
    RendererComponent* renderer = entity->getComponent<RendererComponent>("renderer");
    if (!renderer) return;

    // Build model matrix from transform
    float modelMatrix[16];
    buildModelMatrix(*transform, modelMatrix);

    // Render using the component (shader handles both textured and solid colour)
    renderer->render(shader.get(), modelMatrix);
}

void SceneRenderer::buildModelMatrix(const TransformComponent& transform, float* outMatrix) {
    // Simple 2D model matrix: translation + scale (no rotation for simplicity)
    // For 2D, we ignore z translation but can use it for depth sorting later
    
    std::memset(outMatrix, 0, 16 * sizeof(float));
    
    // Scale
    outMatrix[0] = transform.scale.x;
    outMatrix[5] = transform.scale.y;
    outMatrix[10] = transform.scale.z;
    outMatrix[15] = 1.0f;
    
    // Translation
    outMatrix[12] = transform.position.x;
    outMatrix[13] = transform.position.y;
    outMatrix[14] = transform.position.z;
}
