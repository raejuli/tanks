#include "Tree.h"
#include <queue>

void Tree::addChild(Tree* child) {
    this->children.push_back(child);
}

void Tree::removeChild(Tree* child) {
    std::erase(this->children, child);
}

std::vector<Tree*>& Tree::getChildren() {
    return this->children;
}

