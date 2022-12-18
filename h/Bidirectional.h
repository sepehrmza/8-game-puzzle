//
// Created by Sepehr on 12/31/2020.
//

#ifndef MIDETERM_PROJECT_BIDIRECTIONAL_H
#define MIDETERM_PROJECT_BIDIRECTIONAL_H
#include "matrix.h"

class Bidirectional {
public:
    Bidirectional() = default;
    void createTree(Matrix matrix);
    void show_solution();

    bool goalFound = false;

private:
    std::vector<Matrix> path_to_solution_first;
    std::vector<Matrix> path_to_solution_second;
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

    template<typename T>
    bool find_nodes(T node, std::vector<std::shared_ptr<T>>);

    class Node{
    public:
        Node() = default;
        Node(const Node &node);
        Matrix value;
        std::shared_ptr<Node> parent{nullptr};
        std::vector<std::shared_ptr<Node>> children;
        explicit Node(const Matrix& _value);
        //bool operator==(const Node& node) const;
    };
};


#endif //MIDETERM_PROJECT_BIDIRECTIONAL_H
