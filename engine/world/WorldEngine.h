#ifndef ENGINE_WORLDENGINE_H
#define ENGINE_WORLDENGINE_H

#include "input/InputManager.h"
#include "renderer/SceneRenderer.h"
#include "scene/SceneTree.h"
#include "window/Window.h"

struct ISystems {
    InputManager inputManager;
};

template<typename TSystems>
    requires std::derived_from<TSystems, ISystems>
class WorldEngine final {
public:
    WorldEngine() = default;
    ~WorldEngine() = default;

    void build(TSystems systems, SceneTree* scene, SceneRenderer* renderer, GLFWwindow* window, Camera* camera);
    void start();

private:
    TSystems systems;
    SceneTree* scene;
    SceneRenderer* renderer;
    GLFWwindow* window;
    Camera* camera;

    float lastFrame = 0.0f;

    void update();
    void systemsTick();
    void worldTick();
    // void physicsTick();
    void renderTick();
};

#include "WorldEngine.tpp"


#endif //ENGINE_WORLDENGINE_H