#ifndef ENGINE_TRANSFORMCOMPONENT_H
#define ENGINE_TRANSFORMCOMPONENT_H

#include "component/Component.h"

struct Vector3 {
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};

class TransformComponent : public Component {
public:
    TransformComponent() : position{0.0f, 0.0f, 0.0f}, scale{1.0f, 1.0f, 1.0f} {}
    
    Vector3 position;
    Vector3 scale;
};


#endif //ENGINE_TRANSFORMCOMPONENT_H