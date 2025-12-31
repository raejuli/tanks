#include "Entity.h"

Entity::Entity() : uuid(0) {}

bool Entity::addComponent(std::string name, Component component) {
    return this->components.insert({name, component}).second;
}

Component Entity::getComponent(std::string name) {
    return this->components.at(name);
}

bool Entity::removeComponent(std::string name) {
    return this->components.erase(name);
}


