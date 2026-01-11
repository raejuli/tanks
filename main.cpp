#include <iostream>
#include <ostream>

// glad must be included before GLFW
#include <glad/glad.h>
#include <glfw3.h>

#include "assets/AssetManager.h"
#include "entity/Entity.h"
#include "input/InputManager.h"
#include "scene/SceneTree.h"
#include "transform/TransformComponent.h"
#include "renderer/Camera.h"
#include "renderer/SceneRenderer.h"
#include "renderer/components/QuadRenderer.h"
#include "renderer/components/Texture2DComponent.h"
#include "world/WorldEngine.h"

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

    auto* inputManager = new InputManager();
    WorldEngine<ServiceContainer> we = WorldEngine<ServiceContainer>{};
    ServiceContainer services{};
    services.inputManager = std::unique_ptr<InputManager>(inputManager);
    we.build(std::move(services), &scene, &sceneRenderer, window, &perspectiveCamera);
    we.start();

    glfwTerminate();
    return 0;
}