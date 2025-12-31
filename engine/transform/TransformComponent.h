#ifndef ENGINE_TRANSFORMCOMPONENT_H
#define ENGINE_TRANSFORMCOMPONENT_H

#include "component/Component.h"

struct Vector3 {
    float x, y, z;
};

class TransformComponent : public Component {
public:
    Vector3 position;
};


#endif //ENGINE_TRANSFORMCOMPONENT_H