#ifndef ENGINE_ENTITY_H
#define ENGINE_ENTITY_H

#include <unordered_map>
#include <string>
#include <concepts>
#include <stdexcept>

#include "../component/Component.h"

class Entity {
public:
    Entity();
    ~Entity();

    template<typename TComponent>
        requires std::derived_from<TComponent, Component>
    bool addComponent(std::string name, TComponent* component);
    bool removeComponent(std::string name);
    template<typename TComponent>
        requires std::derived_from<TComponent, Component>
    TComponent& getComponent(std::string name);
protected:
    long long uuid;
private:
    std::unordered_map<std::string, Component*> components;  // name -> component
};


// Template method definitions must be available at the point of instantiation,
// so we provide them in the header for now, may move to a .tpp file in the future
template<typename TComponent>
    requires std::derived_from<TComponent, Component>
bool Entity::addComponent(std::string name, TComponent* component) {
    return this->components.insert({name, static_cast<Component*>(component)}).second;
}

template<typename TComponent>
    requires std::derived_from<TComponent, Component>
TComponent& Entity::getComponent(std::string name) {
    const auto it = this->components.find(name);

    if (auto* p = dynamic_cast<TComponent*>(it->second)) {
        return *p;
    }
    throw std::bad_cast();
}


#endif //ENGINE_ENTITY_H