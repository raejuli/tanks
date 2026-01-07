#include <iostream>
#include <ostream>

// glad must be included before GLFW
#include <glad/glad.h>
#include <glfw3.h>
#include <memory>

#include "assets/AssetManager.h"
#include "entity/Entity.h"
#include "scene/SceneTree.h"
#include "transform/TransformComponent.h"
#include "renderer/Camera.h"
#include "renderer/SceneRenderer.h"
#include "renderer/components/QuadRenderer.h"
#include "renderer/components/Texture2DComponent.h"

// Global variables for mouse handling
double lastMouseX = 400.0;
double lastMouseY = 300.0;
bool firstMouse = true;
bool mouseCaptured = false;
Camera* activeCamera = nullptr;  // Pointer to currently active camera

// Mouse callback for FPS-style camera rotation
void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    if (!activeCamera || !mouseCaptured) return;

    if (firstMouse) {
        lastMouseX = xpos;
        lastMouseY = ypos;
        firstMouse = false;
    }

    float deltaX = static_cast<float>(xpos - lastMouseX);
    float deltaY = static_cast<float>(ypos - lastMouseY);
    lastMouseX = xpos;
    lastMouseY = ypos;

    activeCamera->processMouseMovement(deltaX, deltaY, 0.1f);
}

// Mouse button callback to toggle mouse capture
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        mouseCaptured = !mouseCaptured;
        if (mouseCaptured) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            firstMouse = true;  // Reset to prevent jump
        } else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }
}

int main() {
    // test linking static engine lib
    std::cout << test() << std::endl;
    std::cout << "Hello World!" << std::endl;

    // Initialize GLFW and create OpenGL context BEFORE loading GLAD
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    ///////////////////////////////
    // todo use the Window class
    ///////////////////////////////

    GLFWwindow* window = glfwCreateWindow(800, 600, "Tanks - Camera Test", NULL, NULL);
    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Load OpenGL function pointers with GLAD AFTER a context is current
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glEnable(GL_DEPTH_TEST);  // Enable depth testing for 3D

    // ==================== CAMERA SETUP ====================
    
    // Create perspective camera (FOV 45 degrees, aspect ratio 800/600)
    PerspectiveCamera perspectiveCamera(90.0f, 800.0f / 600.0f, 0.1f, 1000.0f);
    perspectiveCamera.setPosition(0.0f, 5.0f, 15.0f);
    perspectiveCamera.setRotation(-90.0f, -15.0f);  // Look slightly down
    
    // Create orthographic camera for
    // Larger bounds to see more of the scene
    // OrthographicCamera orthoCamera(-15.0f * (800.0f/600.0f), 15.0f * (800.0f/600.0f), -15.0f, 15.0f, -100.0f, 100.0f);
    // orthoCamera.setPosition(0.0f, 0.0f, 20.0f);  // Centered, looking at origin
    // orthoCamera.setRotation(-90.0f, 0.0f);  // Look straight ahead (no pitch)

    activeCamera = &perspectiveCamera;

    // Set up mouse callbacks
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);

    // Create scene renderer
    SceneRenderer sceneRenderer;
    sceneRenderer.initialize();
    sceneRenderer.setCamera(activeCamera);

    // ==================== TEST SCENE SETUP ====================
    SceneTree scene("main");

    // Create a grid of quads
    // Row 1: Near quads (Z = 0)
    Entity* redQuad = new Entity("redQuad");
    redQuad->addComponent("renderer", new QuadRenderer(1.0f, 0.0f, 0.0f, 1.0f));
    redQuad->getComponent<TransformComponent>("transform")->position = {-4.0f, 0.0f, 0.0f};
    redQuad->getComponent<TransformComponent>("transform")->scale = {2.0f, 2.0f, 1.0f};
    scene.addChild(redQuad);

    Entity* greenQuad = new Entity("greenQuad");
    greenQuad->addComponent("texture", new Texture2DComponent("textures/test.png"));
    greenQuad->addComponent("renderer", new QuadRenderer());  // White color for no tint
    greenQuad->getComponent<TransformComponent>("transform")->position = {0.0f, 0.0f, 0.0f};
    greenQuad->getComponent<TransformComponent>("transform")->scale = {5.0f, 5.0f, 1.0f};
    scene.addChild(greenQuad);

    Entity* blueQuad = new Entity("blueQuad");
    blueQuad->addComponent("renderer", new QuadRenderer(0.0f, 0.0f, 1.0f, 1.0f));
    blueQuad->getComponent<TransformComponent>("transform")->position = {4.0f, 0.0f, 0.0f};
    blueQuad->getComponent<TransformComponent>("transform")->scale = {2.0f, 2.0f, 1.0f};
    scene.addChild(blueQuad);

    // Row 2: Mid quads (Z = -5)
    Entity* yellowQuad = new Entity("yellowQuad");
    yellowQuad->addComponent("renderer", new QuadRenderer(1.0f, 1.0f, 0.0f, 1.0f));
    yellowQuad->getComponent<TransformComponent>("transform")->position = {-4.0f, 0.0f, -5.0f};
    yellowQuad->getComponent<TransformComponent>("transform")->scale = {2.0f, 2.0f, 1.0f};
    scene.addChild(yellowQuad);

    Entity* cyanQuad = new Entity("cyanQuad");
    cyanQuad->addComponent("renderer", new QuadRenderer(0.0f, 1.0f, 1.0f, 1.0f));
    cyanQuad->getComponent<TransformComponent>("transform")->position = {0.0f, 0.0f, -5.0f};
    cyanQuad->getComponent<TransformComponent>("transform")->scale = {2.0f, 2.0f, 1.0f};
    scene.addChild(cyanQuad);

    Entity* magentaQuad = new Entity("magentaQuad");
    magentaQuad->addComponent("renderer", new QuadRenderer(1.0f, 0.0f, 1.0f, 1.0f));
    magentaQuad->getComponent<TransformComponent>("transform")->position = {4.0f, 0.0f, -5.0f};
    magentaQuad->getComponent<TransformComponent>("transform")->scale = {2.0f, 2.0f, 1.0f};
    scene.addChild(magentaQuad);

    // Row 3: Far quads (Z = -10)
    Entity* orangeQuad = new Entity("orangeQuad");
    orangeQuad->addComponent("renderer", new QuadRenderer(1.0f, 0.5f, 0.0f, 1.0f));
    orangeQuad->getComponent<TransformComponent>("transform")->position = {-4.0f, 0.0f, -10.0f};
    orangeQuad->getComponent<TransformComponent>("transform")->scale = {2.0f, 2.0f, 1.0f};
    scene.addChild(orangeQuad);

    Entity* whiteQuad = new Entity("whiteQuad");
    whiteQuad->addComponent("renderer", new QuadRenderer(1.0f, 1.0f, 1.0f, 1.0f));
    whiteQuad->getComponent<TransformComponent>("transform")->position = {0.0f, 0.0f, -10.0f};
    whiteQuad->getComponent<TransformComponent>("transform")->scale = {2.0f, 2.0f, 1.0f};
    scene.addChild(whiteQuad);

    Entity* grayQuad = new Entity("grayQuad");
    grayQuad->addComponent("renderer", new QuadRenderer(0.5f, 0.5f, 0.5f, 1.0f));
    grayQuad->getComponent<TransformComponent>("transform")->position = {4.0f, 0.0f, -10.0f};
    grayQuad->getComponent<TransformComponent>("transform")->scale = {2.0f, 2.0f, 1.0f};
    scene.addChild(grayQuad);

    std::cout << "\n==================== CONTROLS ====================" << std::endl;
    std::cout << "  WASD        - Move camera" << std::endl;
    std::cout << "  Space/Shift - Move up/down" << std::endl;
    std::cout << "  Right-click - Toggle mouse look" << std::endl;
    std::cout << "  TAB         - Switch camera (Perspective/Orthographic)" << std::endl;
    std::cout << "  Q/E         - Zoom out/in (Orthographic only)" << std::endl;
    std::cout << "  ESC         - Exit" << std::endl;
    std::cout << "==================================================" << std::endl;

    // Timing for smooth movement
    float lastFrame = 0.0f;
    bool tabPressed = false;

    // ==================== MAIN RENDER LOOP ====================
    while (!glfwWindowShouldClose(window)) {
        // Calculate delta time
        float currentFrame = static_cast<float>(glfwGetTime());
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Handle input
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }

        // Switch camera with TAB
        if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS && !tabPressed) {
            tabPressed = true;
            
            // Copy position and rotation from current camera to new camera
            float x, y, z;
            activeCamera->getPosition(x, y, z);
            float yaw = activeCamera->getYaw();
            float pitch = activeCamera->getPitch();

            activeCamera = &perspectiveCamera;
            std::cout << "Switched to: PERSPECTIVE camera" << std::endl;
            
            activeCamera->setPosition(x, y, z);
            activeCamera->setRotation(yaw, pitch);
            sceneRenderer.setCamera(activeCamera);
        }
        if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_RELEASE) {
            tabPressed = false;
        }

        // Zoom for orthographic camera
        // if (!usePerspective) {
        //     if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        //         orthoCamera.setZoom(orthoCamera.getZoom() * (1.0f - deltaTime));
        //     }
        //     if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        //         orthoCamera.setZoom(orthoCamera.getZoom() * (1.0f + deltaTime));
        //     }
        // }

        // Camera movement (WASD + Space/Shift)
        float cameraSpeed = 5.0f * deltaTime;
        
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            activeCamera->moveForward(cameraSpeed);
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            activeCamera->moveForward(-cameraSpeed);
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            activeCamera->moveRight(-cameraSpeed);
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            activeCamera->moveRight(cameraSpeed);
        }
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            activeCamera->moveUp(cameraSpeed);
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
            activeCamera->moveUp(-cameraSpeed);
        }

        // Clear and render
        sceneRenderer.clear(0.1f, 0.1f, 0.15f, 1.0f);
        sceneRenderer.render(&scene);

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

