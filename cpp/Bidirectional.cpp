//
// Created by Sepehr on 12/31/2020.
//

#include "Bidirectional.h"

template<typename T>
void Bidirectional::set_children(T &node) {
    if(!node.parent) {
        if (!node.value.isSame(node.value.moveRight())) {
            node.children.push_back(std::make_shared<T>(setRight(node)));
            node.children[node.children.size() - 1]->parent = std::make_shared<T>(node);
        }
        if (!node.value.isSame(node.value.moveLeft())) {
            node.children.push_back(std::make_shared<T>(setLeft(node)));
            node.children[node.children.size() - 1]->parent = std::make_shared<T>(node);
        }
        if (!node.value.isSame(node.value.moveUp())) {
            node.children.push_back(std::make_shared<T>(setUp(node)));
            node.children[node.children.size() - 1]->parent = std::make_shared<T>(node);
        }
        if (!node.value.isSame(node.value.moveDown())) {
            node.children.push_back(std::make_shared<T>(setDown(node)));
            node.children[node.children.size() - 1]->parent = std::make_shared<T>(node);
        }
        return;
    }
    if(!node.parent->parent) {
        if (!node.value.isSame(node.value.moveRight())) {
            node.children.push_back(std::make_shared<T>(setRight(node)));
            node.children[node.children.size() - 1]->parent = std::make_shared<T>(node);
        }
        if (!node.value.isSame(node.value.moveLeft())) {
            node.children.push_back(std::make_shared<T>(setLeft(node)));
            node.children[node.children.size() - 1]->parent = std::make_shared<T>(node);
        }
        if (!node.value.isSame(node.value.moveUp())) {
            node.children.push_back(std::make_shared<T>(setUp(node)));
            node.children[node.children.size() - 1]->parent = std::make_shared<T>(node);
        }
        if (!node.value.isSame(node.value.moveDown())) {
            node.children.push_back(std::make_shared<T>(setDown(node)));
            node.children[node.children.size() - 1]->parent = std::make_shared<T>(node);
        }
    } else{
        if (!node.value.isSame(node.value.moveRight()) && !node.value.moveRight().isSame(node.parent->parent->value)) {
            node.children.push_back(std::make_shared<T>(setRight(node)));
            node.children[node.children.size() - 1]->parent = std::make_shared<T>(node);
        }
        if (!node.value.isSame(node.value.moveLeft()) && !node.value.moveLeft().isSame(node.parent->parent->value)) {
            node.children.push_back(std::make_shared<T>(setLeft(node)));
            node.children[node.children.size() - 1]->parent = std::make_shared<T>(node);
        }
        if (!node.value.isSame(node.value.moveUp()) && !node.value.moveUp().isSame(node.parent->parent->value)) {
            node.children.push_back(std::make_shared<T>(setUp(node)));
            node.children[node.children.size() - 1]->parent = std::make_shared<T>(node);
        }
        if (!node.value.isSame(node.value.moveDown()) && !node.value.moveDown().isSame(node.parent->parent->value)) {
            node.children.push_back(std::make_shared<T>(setDown(node)));
            node.children[node.children.size() - 1]->parent = std::make_shared<T>(node);
        }
    }
}

template<typename T>
T Bidirectional::setRight(T node) {
    T nodeRight(node.value.moveRight());
    return nodeRight;
}

template<typename T>
T Bidirectional::setLeft(T node) {
    T nodeLeft(node.value.moveLeft());
    return nodeLeft;
}

template<typename T>
T Bidirectional::setUp(T node) {
    T nodeUp(node.value.moveUp());
    return nodeUp;
}

template<typename T>
T Bidirectional::setDown(T node) {
    T nodeDown(node.value.moveDown());
    return nodeDown;
}

template<typename T>
bool Bidirectional::isGoal(T node, T rootNode) {
    bool isGoal = false;
    Matrix goalMatrix{rootNode.value.getGoal()};
    if(goalMatrix.isSame(node.value)){
        isGoal = true;
    }
    return isGoal;
}

void Bidirectional::createTree(Matrix matrix) {
    Node root(matrix);
    Matrix goal_matrix{matrix.getGoal()};
    Node goal_root(goal_matrix);
    if(matrix == goal_matrix){
        std::cout << "your matrix is your goal!! \n";

        goalFound = true;
        return;
    }
    std::vector<std::shared_ptr<Node>> direct_traversal{};
    std::vector<std::shared_ptr<Node>> reverse_traversal{};
    direct_traversal.push_back(std::make_shared<Node>(root));
    reverse_traversal.push_back(std::make_shared<Node>(goal_root));
    int i{};
    int flg{0};
    while(true){
        if(i > 100000){
            std::cout << "max iterations passed" << std::endl;
            break;
        }
        set_children(*direct_traversal[i]);
        for(size_t j{0}; j < direct_traversal[i]->children.size(); j++){
            direct_traversal.push_back(direct_traversal[i]->children[j]);
            if(find_nodes(*direct_traversal[direct_traversal.size() - 1], reverse_traversal)){
                goalFound = true;
                flg = 10;
                break;
            }
        }
        if(flg == 10){
            break;
        }
        set_children(*reverse_traversal[i]);
        for(size_t j{0}; j < reverse_traversal[i]->children.size(); j++){
            reverse_traversal.push_back(reverse_traversal[i]->children[j]);
            if(find_nodes(*reverse_traversal[reverse_traversal.size() - 1], direct_traversal)){
                goalFound = true;
                flg = 11;
                break;
            }
        }
        if(flg == 11){
            break;
        }
        i++;
    }
    std::cout << "Goal Found" << std::endl;
    if(goalFound){
        if(flg == 10){
            std::shared_ptr<Node> node{direct_traversal[direct_traversal.size() - 1]};
            auto iter = std::find_if(reverse_traversal.begin(), reverse_traversal.end(),
                    [node](std::shared_ptr<Node> n){
                return n->value.isSame(node->value);
            });
            std::shared_ptr<Node> node1 = *iter;
            while(node1->parent){
                path_to_solution_second.push_back(node1->value);
                node1 = node1->parent;
            }
            path_to_solution_second.push_back(goal_matrix);
            std::shared_ptr<Node> node2 = direct_traversal[direct_traversal.size() - 1];
            while(node2->parent){
                path_to_solution_first.push_back(node2->value);
                node2 = node2->parent;
            }
            path_to_solution_first.push_back(root.value);
            reverse(path_to_solution_first.begin(), path_to_solution_first.end());
        }
        if(flg == 11) {
            std::shared_ptr<Node> node{reverse_traversal[reverse_traversal.size() - 1]};
            auto iter = std::find_if(direct_traversal.begin(), direct_traversal.end(),
                                  [node](std::shared_ptr<Node> n){
                                      return n->value.isSame(node->value);
                                  });
            std::shared_ptr<Node> node1 = *iter;
            while(node1->parent){
                path_to_solution_first.push_back(node1->value);
                node1 = node1->parent;
            }
            path_to_solution_first.push_back(goal_matrix);
            std::shared_ptr<Node> node2 = reverse_traversal[reverse_traversal.size() - 1];
            while(node2->parent){
                path_to_solution_second.push_back(node2->value);
                node2 = node2->parent;
            }
            path_to_solution_second.push_back(goal_matrix);
            reverse(path_to_solution_first.begin(), path_to_solution_first.end());
        }
    }
}

template<typename T>
bool Bidirectional::find_nodes(T node, std::vector<std::shared_ptr<T>> vector) {
    bool find{false};
    auto iter = std::find_if(vector.begin(), vector.end(), [node](std::shared_ptr<T> n){
        return n->value.isSame(node.value);
    });
    if(iter != vector.end()){
        find = true;
    }
    return find;
}

void Bidirectional::show_solution() {
    std::vector<Matrix> v{};
    path_to_solution_first.insert(
            path_to_solution_first.end(),
            path_to_solution_second.begin(),
            path_to_solution_second.end()
            );
    v = path_to_solution_first;
    auto end = v.end();
    for (auto it = v.begin(); it != end; ++it) {
        end = std::remove(it + 1, end, *it);
    }
    v.erase(end, v.end());
    for(size_t s{}; s < v.size(); s++){
        std::cout << "Iter "<< s+1 << std::endl;
        v[s].show();
    }
}

Bidirectional::Node::Node(const Matrix &_value) : value{_value} {

}

//bool Bidirectional::Node::operator==(const Bidirectional::Node &node) const {
//    return this->value.isSame(node.value);
//}

Bidirectional::Node::Node(Bidirectional::Node const &node) {
    children = node.children;
    value = node.value;
    parent = node.parent;
}
