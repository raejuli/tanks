#ifndef ENGINE_TREE_H
#define ENGINE_TREE_H

#include <functional>
#include <concepts>
#include <queue>
#include <vector>


class Tree {
public:
    // Ensure polymorphic behavior for safe dynamic_casts
    virtual ~Tree() = default;
    void addChild(Tree* child);
    void removeChild(Tree* child);
    std::vector<Tree*>& getChildren();

    // Breadth-first tree traverse
    template<typename T>
    requires std::derived_from<T, Tree>
    static void Traverse(Tree* tree, std::function<void(T*)> callback);

protected:

private:
    std::vector<Tree*> children = {};
};

template<typename T>
    requires std::derived_from<T, Tree>
void Tree::Traverse(Tree* tree, std::function<void(T*)> callback) {
    std::queue<Tree*> q;

    for (auto child : tree->getChildren()) {
        q.push(child);
    }

    while (!q.empty()) {
        Tree* current = q.front();
        q.pop();

        // if (auto* typed = dynamic_cast<T*>(current)) {
        //     callback(typed);
        // }

        callback(dynamic_cast<T*>(current));

        for (auto child : current->getChildren()) {
            q.push(child);
        }
    }
}


#endif //ENGINE_TREE_H