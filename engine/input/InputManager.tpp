#ifndef ENGINE_INPUTMANAGER_TH
#define ENGINE_INPUTMANAGER_TH

#include "InputManager.h"

void InputManager::update(int dt) {

}

bool InputManager::isKeyPressed(Key key) {
    return true;
}

bool InputManager::isKeyJustPressed(Key key) {
    return true;
}

bool InputManager::isKeyJustReleased(Key key) {
    return true;
}

bool InputManager::isMouseButtonPressed(MouseButton button) {
    return true;
}

bool InputManager::isMouseButtonJustPressed(MouseButton button) {
    return true;
}

bool InputManager::isMouseButtonJustReleased(MouseButton button) {
    return true;
}

void InputManager::bindAction(std::string_view, Key key) {

}

void InputManager::bindAction(std::string_view action, MouseButton button) {

}

bool InputManager::isActionPressed(std::string_view action) {
    return true;
}

bool InputManager::isActionJustPressed(std::string_view action) {
    return true;
}


#endif //ENGINE_INPUTMANAGER_TH