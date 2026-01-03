#ifndef ENGINE_WINDOW_H
#define ENGINE_WINDOW_H

#include <glfw3.h>

class Window {
public:
    Window();
    ~Window();
protected:

private:
    GLFWwindow* _window;
};


#endif //ENGINE_WINDOW_H