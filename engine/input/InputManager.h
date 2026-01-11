#ifndef ENGINE_INPUTMANAGER_H
#define ENGINE_INPUTMANAGER_H

#include <string>
#include <unordered_map>
#include <glfw3.h>

#include "service/IService.h"


enum class Key {
    A, S, D, W, Space, Shift, Escape
};

enum class MouseButton {
    Left, Right
};

class InputManager : public IService{
public:
    // no implicit conversions
    explicit InputManager(GLFWwindow* window);

    // IService interface
    void update(int dt) override;

    bool isKeyPressed(Key key);      // True while held down
    bool isKeyJustPressed(Key key);  // True only on the frame it was pressed
    bool isKeyJustReleased(Key key); // True only on the frame it was released

    bool isMouseButtonPressed(MouseButton button);
    bool isMouseButtonJustPressed(MouseButton button);
    bool isMouseButtonJustReleased(MouseButton button);

    void bindAction(std::string_view action, Key key);
    void bindAction(std::string_view action, MouseButton button);

    bool isActionPressed(std::string_view action);      // "jump", "fire"
    bool isActionJustPressed(std::string_view action);

protected:

private:
    GLFWwindow* window;

    // State tracking for edge detection
    std::unordered_map<Key, bool> currentKeyStates;
    std::unordered_map<Key, bool> previousKeyStates;
    std::unordered_map<MouseButton, bool> currentMouseStates;
    std::unordered_map<MouseButton, bool> previousMouseStates;

    // Action bindings
    std::unordered_map<std::string, Key> keyBindings;
    std::unordered_map<std::string, MouseButton> mouseBindings;

    // Helper to convert Key enum to GLFW key code
    static int keyToGLFW(Key key);
    static int mouseButtonToGLFW(MouseButton button);
};

#include "./InputManager.tpp"


#endif //ENGINE_INPUTMANAGER_H