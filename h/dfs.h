//
// Created by Sepehr on 12/26/2020.
//

#ifndef MIDETERM_PROJECT_DFS_H
#define MIDETERM_PROJECT_DFS_H
#include "matrix.h"

class DFS {
public:
    DFS() = default;
    void createTree(const Matrix& root, size_t maxDepth = 7);
    void show_solution();

    bool goalFound = false;
private:
    std::vector<Matrix> path_to_solution;

    template<typename T>
    void set_children(T& node);

    template<typename T>
    T setRight(T node);

    template<typename T>
    T setLeft(T node);

    template<typename T>
    T setUp(T node);

    template<typename T>
    T setDown(T node);

    template<typename T>
    bool isGoal(T node, T rootNode);
    class Node{
    public:
        Node() = default;
        Matrix value;
        std::shared_ptr<Node> parent{nullptr};
        std::vector<std::shared_ptr<Node>> children;
        explicit Node(const Matrix& _value);
        int count_depth();
    };
};


#endif //MIDETERM_PROJECT_DFS_H
