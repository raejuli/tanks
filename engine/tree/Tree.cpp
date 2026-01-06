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

void Tree::Traverse(Tree* tree, void(*callback)(Tree* tree)) {
    std::queue<Tree*> q;

    for (auto child : tree->getChildren()) {
        q.push(child);
    }

    while (!q.empty()) {
        Tree* current = q.front();
        q.pop();

        callback(current);

        for (auto child : current->getChildren()) {
            q.push(child);
        }
    }
}
