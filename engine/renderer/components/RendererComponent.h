#ifndef ENGINE_RENDERERCOMPONENT_H
#define ENGINE_RENDERERCOMPONENT_H

#include "component/Component.h"
#include "../shader/Shader.h"

// Base class for all renderer components
// Derived classes implement specific rendering (quad, mesh, cube, etc.)
class RendererComponent : public Component {
public:
    RendererComponent() = default;
    virtual ~RendererComponent() = default;

    // Initialize OpenGL resources (VAO, VBO, etc.)
    virtual void initialize() = 0;
    
    // Render the component using the provided shader and camera matrices
    virtual void render(Shader* shader, const float* modelMatrix) = 0;
    
    // Cleanup OpenGL resources
    virtual void cleanup() = 0;

    // Check if the component has been initialized
    bool isInitialized() const { return initialized; }

protected:
    bool initialized = false;
};

#endif //ENGINE_RENDERERCOMPONENT_H
