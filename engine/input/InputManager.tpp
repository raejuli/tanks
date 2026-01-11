#ifndef ENGINE_INPUTMANAGER_TH
#define ENGINE_INPUTMANAGER_TH

#include "InputManager.h"

InputManager::InputManager(GLFWwindow* window) : window(window) {
    // Initialize all key states to false
    // todo improve this in the future need to add all keys
    for (Key key : {Key::A, Key::S, Key::D, Key::W, Key::Space, Key::Shift, Key::Escape}) {
        currentKeyStates[key] = false;
        previousKeyStates[key] = false;
    }
    
    // Initialize mouse button states
    for (MouseButton btn : {MouseButton::Left, MouseButton::Right}) {
        currentMouseStates[btn] = false;
        previousMouseStates[btn] = false;
    }
}

// Convert Key enum to GLFW key code
int InputManager::keyToGLFW(Key key) {
    switch (key) {
        case Key::A: return GLFW_KEY_A;
        case Key::S: return GLFW_KEY_S;
        case Key::D: return GLFW_KEY_D;
        case Key::W: return GLFW_KEY_W;
        case Key::Space: return GLFW_KEY_SPACE;
        case Key::Shift: return GLFW_KEY_LEFT_SHIFT;
        case Key::Escape: return GLFW_KEY_ESCAPE;
        default: return GLFW_KEY_UNKNOWN;
    }
}

// Convert MouseButton enum to GLFW mouse button code
int InputManager::mouseButtonToGLFW(MouseButton button) {
    switch (button) {
        case MouseButton::Left: return GLFW_MOUSE_BUTTON_LEFT;
        case MouseButton::Right: return GLFW_MOUSE_BUTTON_RIGHT;
        default: return -1;
    }
}

void InputManager::update(int dt) {
    // Copy current states to previous states
    previousKeyStates = currentKeyStates;
    previousMouseStates = currentMouseStates;

    // Poll all tracked keys
    for (auto& [key, state] : currentKeyStates) {
        state = glfwGetKey(window, keyToGLFW(key)) == GLFW_PRESS;
    }

    // Poll all tracked mouse buttons
    for (auto& [button, state] : currentMouseStates) {
        state = glfwGetMouseButton(window, mouseButtonToGLFW(button)) == GLFW_PRESS;
    }
}

bool InputManager::isKeyPressed(Key key) {
    return currentKeyStates[key];
}

bool InputManager::isKeyJustPressed(Key key) {
    return currentKeyStates[key] && !previousKeyStates[key];
}

bool InputManager::isKeyJustReleased(Key key) {
    return !currentKeyStates[key] && previousKeyStates[key];
}

bool InputManager::isMouseButtonPressed(MouseButton button) {
    return currentMouseStates[button];
}

bool InputManager::isMouseButtonJustPressed(MouseButton button) {
    return currentMouseStates[button] && !previousMouseStates[button];
}

bool InputManager::isMouseButtonJustReleased(MouseButton button) {
    return !currentMouseStates[button] && previousMouseStates[button];
}

void InputManager::bindAction(std::string_view action, Key key) {
    keyBindings[std::string(action)] = key;
}

void InputManager::bindAction(std::string_view action, MouseButton button) {
    mouseBindings[std::string(action)] = button;
}

bool InputManager::isActionPressed(std::string_view action) {
    std::string actionStr(action);
    if (keyBindings.contains(actionStr)) {
        return isKeyPressed(keyBindings[actionStr]);
    }
    if (mouseBindings.contains(actionStr)) {
        return isMouseButtonPressed(mouseBindings[actionStr]);
    }
    return false;
}

bool InputManager::isActionJustPressed(std::string_view action) {
    std::string actionStr(action);
    if (keyBindings.contains(actionStr)) {
        return isKeyJustPressed(keyBindings[actionStr]);
    }
    if (mouseBindings.contains(actionStr)) {
        return isMouseButtonJustPressed(mouseBindings[actionStr]);
    }
    return false;
}


#endif //ENGINE_INPUTMANAGER_TH