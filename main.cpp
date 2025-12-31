#include <iostream>
#include <ostream>

#include "assets/AssetManager.h"
#include "entity/Entity.h"

int main() {
    // test linking static engine lib
    std::cout << test() << std::endl;
    std::cout << "Hello World!" << std::endl;

    Entity entity = Entity();
    std::cout << "adding a component: " << entity.addComponent("test", Component()) << std::endl;
    std::cout << "removing a component: " << entity.removeComponent("test") << std::endl;
}
