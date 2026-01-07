#ifndef ENGINE_COMPONENT_H
#define ENGINE_COMPONENT_H
#include <concepts>
#include <string>

class Entity;

class Component {
public:
    Component();
    virtual ~Component() = default;

    template<typename TComponent>
        requires std::derived_from<TComponent, Component>
    TComponent* getComponent(const std::string& name);
    
protected:
    friend class Entity;  // Allow Entity to set the owner
    void setOwner(Entity* entity) { owner = entity; }

private:
    Entity* owner = nullptr;
};

#endif //ENGINE_COMPONENT_H