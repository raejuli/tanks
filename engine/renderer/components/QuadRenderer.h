#ifndef ENGINE_QUADRENDERER_H
#define ENGINE_QUADRENDERER_H

#include "RendererComponent.h"
#include <glad/glad.h>

// A 2D renderer that renders a quad with optional texture
// Looks for a Texture2DComponent on the same entity to use texture data
class QuadRenderer : public RendererComponent {
public:
    // Colour constructor - RGBA (0.0 - 1.0)
    QuadRenderer(float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f);
    
    ~QuadRenderer() override;

    void initialize() override;
    void render(Shader* shader, const float* modelMatrix) override;
    void cleanup() override;

    // Set colour/tint (for solid colour or tinting textured quads)
    void setColour(float r, float g, float b, float a = 1.0f);
    
    // Get colour components
    float getR() const { return colour[0]; }
    float getG() const { return colour[1]; }
    float getB() const { return colour[2]; }
    float getA() const { return colour[3]; }

private:
    GLuint VAO = 0;
    GLuint VBO = 0;
    GLuint EBO = 0;
    
    float colour[4];  // RGBA (solid colour or tint for texture)
};

#endif //ENGINE_QUADRENDERER_H
