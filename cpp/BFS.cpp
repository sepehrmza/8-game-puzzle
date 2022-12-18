//
// Created by Sepehr on 12/17/2020.
//

#include "BFS.h"

void BFS::createTree(const Matrix& root, size_t maxIterations) {
    Node node(root);
    std::vector<std::shared_ptr<Node>> parent;
    parent.push_back(std::make_shared<Node>(node));
    if(isGoal(node, node)){
        std::cout << "your matrix is your goal!\n";
        goalFound = true;
        return;
    }
    int i{0};
    while(true) {
        if(parent[i]->count_depth() == maxIterations+1){
            std::cout << "max iteration passed." << std::endl;
            break;
        }
        if(!parent[i]->parent) {
            if (!parent[i]->value.isSame(parent[i]->value.moveRight())) {
                parent[i]->children.push_back(std::make_shared<Node>(setRight(node)));
                parent.push_back(parent[i]->children[parent[i]->children.size() - 1]);
                parent[parent.size() - 1]->parent = parent[i];
                if (isGoal(*parent[parent.size() - 1], node)) {
                    goalFound = true;
                    break;
                }
            }
            if (!parent[i]->value.isSame(parent[i]->value.moveLeft())) {
                parent[i]->children.push_back(std::make_shared<Node>(setLeft(node)));
                parent.push_back(parent[i]->children[parent[i]->children.size() - 1]);
                parent[parent.size() - 1]->parent = parent[i];
                if (isGoal(*parent[parent.size() - 1], node)) {
                    goalFound = true;
                    break;
                }
            }
            if (!parent[i]->value.isSame(parent[i]->value.moveUp())) {
                parent[i]->children.push_back(std::make_shared<Node>(setUp(node)));
                parent.push_back(parent[i]->children[parent[i]->children.size() - 1]);
                parent[parent.size() - 1]->parent = parent[i];
                if (isGoal(*parent[parent.size() - 1], node)) {
                    goalFound = true;
                    break;
                }
            }
            if (!parent[i]->value.isSame(parent[i]->value.moveDown())) {
                parent[i]->children.push_back(std::make_shared<Node>(setDown(node)));
                parent.push_back(parent[i]->children[parent[i]->children.size() - 1]);
                parent[parent.size() - 1]->parent = parent[i];
                if (isGoal(*parent[parent.size() - 1], node)) {
                    goalFound = true;
                    break;
                }
            }
        } else {
            if (!parent[i]->value.isSame(parent[i]->value.moveRight()) && !parent[i]->value.moveRight().isSame(parent[i]->parent->value)) {
                parent[i]->children.push_back(std::make_shared<Node>(setRight(*parent[i])));
                parent.push_back(parent[i]->children[parent[i]->children.size() - 1]);
                parent[parent.size() - 1]->parent = parent[i];
                if (isGoal(*parent[parent.size() - 1], node)) {
                    goalFound = true;
                    break;
                }
            }
            if (!parent[i]->value.isSame(parent[i]->value.moveLeft()) && !parent[i]->value.moveLeft().isSame(parent[i]->parent->value)) {
                parent[i]->children.push_back(std::make_shared<Node>(setLeft(*parent[i])));
                parent.push_back(parent[i]->children[parent[i]->children.size() - 1]);
                parent[parent.size() - 1]->parent = parent[i];
                if (isGoal(*parent[parent.size() - 1], node)) {
                    goalFound = true;
                    break;
                }
            }
            if (!parent[i]->value.isSame(parent[i]->value.moveUp()) && !parent[i]->value.moveUp().isSame(parent[i]->parent->value)) {
                parent[i]->children.push_back(std::make_shared<Node>(setUp(*parent[i])));
                parent.push_back(parent[i]->children[parent[i]->children.size() - 1]);
                parent[parent.size() - 1]->parent = parent[i];
                if (isGoal(*parent[parent.size() - 1], node)) {
                    goalFound = true;
                    break;
                }
            }
            if (!parent[i]->value.isSame(parent[i]->value.moveDown()) && !parent[i]->value.moveDown().isSame(parent[i]->parent->value)) {
                parent[i]->children.push_back(std::make_shared<Node>(setDown(*parent[i])));
                parent.push_back(parent[i]->children[parent[i]->children.size() - 1]);
                parent[parent.size() - 1]->parent = parent[i];
                if (isGoal(*parent[parent.size() - 1], node)) {
                    goalFound = true;
                    break;
                }
            }
        }
        i++;
    }
    if(goalFound){
        std::cout << "GOAL HAS FOUND\n";
        size_t size{parent.size() - 1};
        std::shared_ptr<Node> pointer{parent[parent.size() - 1]};
        int flg{0};
        while(pointer->parent) {
            if (flg == 0) {
                path_to_solution.push_back(parent[parent.size() - 1]->value);
                flg = 1;
            }
            path_to_solution.push_back(pointer->parent->value);
            pointer = pointer->parent;
        }
        reverse(path_to_solution.begin(), path_to_solution.end());
    }
}

template<typename T>
T BFS::setRight(T node) {
    T nodeRight(node.value.moveRight());
    return nodeRight;
}

template<typename T>
T BFS::setLeft(T node) {
    T nodeLeft(node.value.moveLeft());
    return nodeLeft;
}

template<typename T>
T BFS::setUp(T node) {
    T nodeUp(node.value.moveUp());
    return nodeUp;
}

template<typename T>
T BFS::setDown(T node) {
    T nodeDown(node.value.moveDown());
    return nodeDown;
}

template<typename T>
bool BFS::isGoal(T node, T rootNode) {
    bool isGoal = false;
    Matrix goalMatrix{rootNode.value.getGoal()};
    if(goalMatrix.isSame(node.value)){
        isGoal = true;
    }
    return isGoal;
}

void BFS::show_solution() {
    if(goalFound) {
        for (size_t i{0}; i < path_to_solution.size(); i++) {
            std::cout << "Iter "<< i+1 << std::endl;
            path_to_solution[i].show();
        }
    } else {
        std::cout << "This puzzle can not be solved :(((" << std::endl;
    }
}

BFS::Node::Node(const Matrix& _value) : value{_value} {

}

bool BFS::Node::operator==(BFS::Node& node) const {
    return node.value == value;
}

int BFS::Node::count_depth() {
    int par{0};
    Node node{*this};
    while(node.parent){
        par++;
        node = *node.parent;
    }
    return par;
}
