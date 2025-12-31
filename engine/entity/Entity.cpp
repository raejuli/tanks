#include "Entity.h"
#include "transform/TransformComponent.h"

Entity::Entity() : uuid(0) {
    this->addComponent("transform", new TransformComponent());  // Every entity should have a transform
}

Entity::~Entity() {
    for (auto& [name, ptr] : components) {
        delete ptr;
    }
    components.clear();
}

bool Entity::removeComponent(std::string name) {
    return this->components.erase(name);
}

