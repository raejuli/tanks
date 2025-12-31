#include <iostream>
#include <ostream>

#include "assets/AssetManager.h"
#include "entity/Entity.h"
#include "transform/TransformComponent.h"

int main() {
    // test linking static engine lib
    std::cout << test() << std::endl;
    std::cout << "Hello World!" << std::endl;

    // test ecs stuff
    Entity entity = Entity();
    std::cout << "adding a component: " << entity.addComponent("test", new Component()) << std::endl;
    std::cout << "removing a component: " << entity.removeComponent("test") << std::endl;

    entity.getComponent<TransformComponent>("transform").position.x = 24;
    std::cout << entity.getComponent<TransformComponent>("transform").position.x << std::endl;
}
