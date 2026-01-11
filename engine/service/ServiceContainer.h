#ifndef ENGINE_SERVICECONTAINER_H
#define ENGINE_SERVICECONTAINER_H

#include <vector>

#include "input/InputManager.h"

struct IEngineInjections {
    std::unique_ptr<InputManager> inputManager;
};

// Concept: must expose iteration
template<typename T>
concept IterableServices = requires(T t) {
    { t.getAll() } -> std::convertible_to<std::vector<IService*>>;
};

template<typename T>
concept ValidServiceContainer = std::derived_from<T, IEngineInjections> && IterableServices<T>;

struct ServiceContainer : IEngineInjections{
    std::vector<IService*> getAll() {
        return {
            inputManager.get(),
        };
    }
};

#endif //ENGINE_SERVICECONTAINER_H