//
// Created by Sepehr on 12/17/2020.
//

#ifndef MIDETERM_PROJECT_BFS_H
#define MIDETERM_PROJECT_BFS_H

#include "matrix.h"

class BFS {
public:
    BFS() = default;
    void createTree(const Matrix& root, size_t maxIterations = 100);
    void show_solution();

    bool goalFound = false;
private:
    std::vector<Matrix> path_to_solution;

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
        bool operator==(Node& node) const;
        int count_depth();
};

};


#endif //MIDETERM_PROJECT_BFS_H
