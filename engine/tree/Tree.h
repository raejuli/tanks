#ifndef ENGINE_TREE_H
#define ENGINE_TREE_H

#include <vector>


class Tree {
public:
    void addChild(Tree* child);
    void removeChild(Tree* child);
    std::vector<Tree*>& getChildren();

    // Breadth-first tree traverse
    static void Traverse(Tree* tree, void (*callback)(Tree* tree));

protected:

private:
    std::vector<Tree*> children = {};
};


#endif //ENGINE_TREE_H