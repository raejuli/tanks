#include <iostream>
#include <ostream>

// glad must be included before GLFW
#include <glad/glad.h>
#include <glfw3.h>

#include "assets/AssetManager.h"
#include "entity/Entity.h"
#include "transform/TransformComponent.h"

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

    // Initialize GLFW and create OpenGL context BEFORE loading GLAD
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    glfwMakeContextCurrent(window);

    // Load OpenGL function pointers with GLAD AFTER a context is current
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glViewport(0, 0, 800, 600);

    while(!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

