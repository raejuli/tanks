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
#include "window/Window.h"

int main() {
    // test linking static engine lib
    std::cout << test() << std::endl;
    std::cout << "Hello World!" << std::endl;

    // test ecs stuff
    Entity entity = Entity();
    std::cout << "adding a component: " << entity.addComponent("test", new Component()) << std::endl;
    std::cout << "removing a component: " << entity.removeComponent("test") << std::endl;

    entity.getComponent<TransformComponent>("transform").position.x = 24;
    std::cout << entity.getComponent<TransformComponent>("transform").position.x << std::endl;

    // test tree stuff
    SceneTree scene = SceneTree("main");
    SceneTree scene1 = SceneTree("test1");
    SceneTree scene2 = SceneTree("test2");
    SceneTree scene3 = SceneTree("test3");
    scene.addChild(&scene1);
    scene.addChild(&scene2);
    scene2.addChild(&scene3);
    std::cout << scene.name << std::endl;
    std::cout << scene.getChildren().size() << std::endl;
    std::cout << scene.getChildren()[1]->getChildren().size() << std::endl;

    // Initialize GLFW and create OpenGL context BEFORE loading GLAD
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    std::unique_ptr<Window> window = std::make_unique<Window>();

    // Load OpenGL function pointers with GLAD AFTER a context is current
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwTerminate();
    return 0;
}

