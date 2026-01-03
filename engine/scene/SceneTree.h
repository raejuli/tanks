#ifndef ENGINE_SCENETREE_H
#define ENGINE_SCENETREE_H

#include <string>

#include "tree/Tree.h"


class SceneTree : public Tree {
public:
    SceneTree(const std::string& name) : name(name) {}
    std::string name;
protected:

private:

};


#endif //ENGINE_SCENETREE_H