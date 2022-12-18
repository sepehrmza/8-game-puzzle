//
// Created by Sepehr on 12/26/2020.
//

#include "dfs.h"

void DFS::createTree(const Matrix &root, size_t maxDepth) {
    Node node(root);
    std::stack<std::shared_ptr<Node>> parent;
    parent.push(std::make_shared<Node>(node));
    if (isGoal(node, node)) {
        std::cout << "your matrix is your goal!\n";
        goalFound = true;
        return;
    }
    parent.pop();
    set_children(node);
    for(int s{0}; s < node.children.size(); s++){
        parent.push(node.children[s]);
    }
    while(true){
        if(parent.empty()){
            std::cout << "Max Iterations Passed" << std::endl;
            break;
        }
        if(parent.top()->count_depth() < maxDepth - 1){
            if(isGoal(*parent.top(), node)){
                goalFound = true;
                break;
            }
            Node next{};
            next = *parent.top();
            parent.pop();
            set_children(next);
            for(int s{0}; s < next.children.size(); s++){
                parent.push(next.children[s]);
            }
        }
        if(parent.top()->count_depth() == maxDepth - 1){
            if(isGoal(*parent.top(), node)){
                goalFound = true;
                break;
            }
            Node next1{};
            next1 = *parent.top();
            parent.pop();
            set_children(next1);
            for(int s{0}; s < next1.children.size(); s++){
                parent.push(next1.children[s]);
            }
            for (size_t i{0}; i < next1.children.size(); ++i) {
                if(isGoal(*parent.top(), node)){
                    goalFound = true;
                    break;
                } else{
                    parent.pop();
                }
            }
        }
    }
    if(goalFound) {
        Node solve{};
        solve = *parent.top();
        while (solve.parent) {
            path_to_solution.push_back(solve.value);
            solve = *solve.parent;
        }
        path_to_solution.push_back(solve.value);
        reverse(path_to_solution.begin(), path_to_solution.end());
    }
}

template<typename T>
bool DFS::isGoal(T node, T rootNode) {
    bool isGoal = false;
    Matrix goalMatrix{rootNode.value.getGoal()};
    if(goalMatrix.isSame(node.value)){
        isGoal = true;
    }
    return isGoal;
}

template<typename T>
T DFS::setRight(T node) {
    T nodeRight(node.value.moveRight());
    return nodeRight;
}

template<typename T>
T DFS::setLeft(T node) {
    T nodeLeft(node.value.moveLeft());
    return nodeLeft;
}

template<typename T>
T DFS::setUp(T node) {
    T nodeUp(node.value.moveUp());
    return nodeUp;
}

template<typename T>
T DFS::setDown(T node) {
    T nodeDown(node.value.moveDown());
    return nodeDown;
}

template<typename T>
void DFS::set_children(T &node) {
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

void DFS::show_solution() {
    if(goalFound) {
        for (size_t i{0}; i < path_to_solution.size(); i++) {
            std::cout << "Iter "<< i+1 << std::endl;
            path_to_solution[i].show();
        }
    } else {
        std::cout << "This puzzle can not be solved :(((" << std::endl;
    }
}

DFS::Node::Node(const Matrix &_value) : value{_value} {

}

int DFS::Node::count_depth() {
    int par{0};
    Node node{*this};
    while(node.parent){
        par++;
        node = *node.parent;
    }
    return par;
}
