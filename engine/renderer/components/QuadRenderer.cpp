#include "QuadRenderer.h"
#include "Texture2DComponent.h"
#include "entity/Entity.h"

QuadRenderer::QuadRenderer(float r, float g, float b, float a) {
    colour[0] = r;
    colour[1] = g;
    colour[2] = b;
    colour[3] = a;
}

QuadRenderer::~QuadRenderer() {
    cleanup();
}

void QuadRenderer::initialize() {
    if (initialized) return;

    // Define a unit quad with texture coordinates
    // Position (3) + TexCoord (2) = 5 floats per vertex
    float vertices[] = {
        // positions          // texture coords
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f,  // bottom-left
         0.5f, -0.5f, 0.0f,   1.0f, 0.0f,  // bottom-right
         0.5f,  0.5f, 0.0f,   1.0f, 1.0f,  // top-right
        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f   // top-left
    };

    // Two triangles to form a quad (counter-clockwise winding)
    unsigned int indices[] = {
        0, 1, 2,  // first triangle
        0, 2, 3   // second triangle
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position attribute (location = 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Texture coord attribute (location = 1)
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    initialized = true;
}

void QuadRenderer::render(Shader* shader, const float* modelMatrix) {
    if (!initialized) {
        initialize();
    }
    
    // Check if entity has a Texture2DComponent
    Texture2DComponent* texComponent = getComponent<Texture2DComponent>("texture");
    bool hasTexture = texComponent && texComponent->isValid();

    shader->use();
    shader->setMat4("model", modelMatrix);
    shader->setVec4("colour", colour[0], colour[1], colour[2], colour[3]);

    // Set texture uniforms
    shader->setInt("useTexture", hasTexture ? 1 : 0);
    
    if (hasTexture) {
        shader->setInt("textureSampler", 0);
        texComponent->getTexture()->bind(0);
    }

    // Enable blending for transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    if (hasTexture) {
        texComponent->getTexture()->unbind();
    }
}

void QuadRenderer::cleanup() {
    if (VAO != 0) {
        glDeleteVertexArrays(1, &VAO);
        VAO = 0;
    }
    if (VBO != 0) {
        glDeleteBuffers(1, &VBO);
        VBO = 0;
    }
    if (EBO != 0) {
        glDeleteBuffers(1, &EBO);
        EBO = 0;
    }
    initialized = false;
}

void QuadRenderer::setColour(float r, float g, float b, float a) {
    colour[0] = r;
    colour[1] = g;
    colour[2] = b;
    colour[3] = a;
}
