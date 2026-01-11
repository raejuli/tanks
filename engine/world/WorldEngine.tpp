#ifndef ENGINE_WORLDENGINE_TPP
#define ENGINE_WORLDENGINE_TPP

#include "WorldEngine.h"
#include <utility>

template<ValidServiceContainer TSystems>
void WorldEngine<TSystems>::build(TSystems systems, SceneTree* scene, SceneRenderer* renderer, GLFWwindow* window, Camera* camera) {
    this->systems = std::move(systems);
    this->scene = scene;
    this->renderer = renderer;
    this->window = window;
    this->camera = camera;
}

template<ValidServiceContainer TSystems>
void WorldEngine<TSystems>::start() {
    update();
}

template<ValidServiceContainer TSystems>
void WorldEngine<TSystems>::update() {
    // Calculate delta time
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    while (!glfwWindowShouldClose(window)) {

        // Handle input
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }

        // Camera movement (WASD + Space/Shift)
        float cameraSpeed = 1.0f * deltaTime;

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            camera->moveForward(cameraSpeed);
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            camera->moveForward(-cameraSpeed);
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            camera->moveRight(-cameraSpeed);
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            camera->moveRight(cameraSpeed);
        }
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            camera->moveUp(cameraSpeed);
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
            camera->moveUp(-cameraSpeed);
        }

        systemsTick();
        worldTick();
        renderTick();

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

template<ValidServiceContainer TSystems>
void WorldEngine<TSystems>::systemsTick() {
    for (const auto& system : systems.getAll()) {
        system->update(deltaTime);
    }
}

template<ValidServiceContainer TSystems>
void WorldEngine<TSystems>::worldTick() {
    Tree::Traverse<SceneTree>(scene, [this](SceneTree* node) {
        if (auto* sceneNode = dynamic_cast<Entity*>(node)) {
            sceneNode->update(deltaTime);
        }
    });
}

template<ValidServiceContainer TSystems>
void WorldEngine<TSystems>::renderTick() {
    // Clear and render
    renderer->clear(0.1f, 0.1f, 0.15f, 1.0f);
    renderer->render(scene);
}

#endif //ENGINE_WORLDENGINE_TPP