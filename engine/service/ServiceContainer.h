#ifndef ENGINE_SERVICECONTAINER_H
#define ENGINE_SERVICECONTAINER_H

#include <vector>
#include <memory>
#include <glfw3.h>

#include "input/InputManager.h"

// Resource container for non-service dependencies (e.g., window, renderer)
struct IEngineResources {
    GLFWwindow* window;
};

// Service traits - specialize for services that need constructor parameters
template<typename T>
struct ServiceTraits {
    static std::unique_ptr<T> create(const IEngineResources& resources) {
        return std::make_unique<T>();
    }
};

// Specialization for InputManager - requires GLFWwindow*
template<>
struct ServiceTraits<InputManager> {
    static std::unique_ptr<InputManager> create(const IEngineResources& resources) {
        return std::make_unique<InputManager>(resources.window);
    }
};

// Service builder that constructs services with their required dependencies
class ServiceBuilder {
public:
    explicit ServiceBuilder(IEngineResources resources) : resources(std::move(resources)) {}

    template<typename T>
    std::unique_ptr<T> build() {
        return ServiceTraits<T>::create(resources);
    }

private:
    IEngineResources resources;
};

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
    // Factory method to create a fully initialized ServiceContainer
    static ServiceContainer create(const IEngineResources& resources) {
        ServiceBuilder builder(resources);
        ServiceContainer container;
        container.inputManager = builder.build<InputManager>();

        return container;
    }

    std::vector<IService*> getAll() {
        return {
            inputManager.get(),
        };
    }
};

#endif //ENGINE_SERVICECONTAINER_H