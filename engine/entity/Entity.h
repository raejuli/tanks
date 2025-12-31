#ifndef ENGINE_ENTITY_H
#define ENGINE_ENTITY_H

#include <unordered_map>
#include <string>

#include "Component.h"

class Entity {
public:
    Entity();

    bool addComponent(std::string name, Component component);        // should template these 3 in the future
    bool removeComponent(std::string name);
    Component getComponent(std::string name);
protected:
    long long uuid;
private:
    std::unordered_map<std::string, Component> components;  // name -> component
};


#endif //ENGINE_ENTITY_H