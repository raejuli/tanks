#include "Window.h"

#include <iostream>

Window::Window() {
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    this->_window = window;
    glfwMakeContextCurrent(window);
    glViewport(0, 0, 800, 600);

    while(!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

Window::~Window() {

}
