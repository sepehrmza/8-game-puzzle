//
// Created by Sepehr on 12/16/2020.
//

#include "matrix.h"


Matrix::Matrix(const std::vector<int>& arr) {
    for (int l = 0; l < 9; ++l) {
        random.push_back(arr[l]);
    }
    std::vector<int> default_goal{1,2,3,4,5,6,7,8,0};
    for (int l = 0; l < 9; ++l) {
        goal.push_back(default_goal[l]);
    }
    int arr1[3][3];
    for(int i{0}; i < 3; i++){
        for(int j{0}; j < 3; j++){
            if(i==0) {
                arr1[i][j] = random[j+i];
            }
            if(i==1){
                arr1[i][j] = random[j+i+2];
            }
            if(i==2){
                arr1[i][j] = random[j+i+4];
            }
        }
    }
    std::vector<std::pair<int, int> > result;
    for (int p = 0; p<3; p++) {
        for (int m = 0; m<3; m++) {
            if (arr1[p][m]==0) {
                result.emplace_back(p, m);
            }
        }
    }
    for(std::vector<std::pair<int, int> >::iterator it = result.begin(); it != result.end(); it++){
        std::vector<std::pair<int, int>>::iterator x;
        zero_loc.first = it->first;
        zero_loc.second = it->second;
    }
}

void Matrix::set_numbers(const std::vector<int>& arr) {
    if(random.empty()){
        for (int i = 0; i < 9; ++i) {
            random.push_back(arr[i]);
        }
        return;
    }
    for(int i{0}; i < 9; i++){
        random[i] = arr[i];
    }
    int arr1[3][3];
    for(int i{0}; i < 3; i++){
        for(int j{0}; j < 3; j++){
            if(i==0) {
                arr1[i][j] = random[j+i];
            }
            if(i==1){
                arr1[i][j] = random[j+i+2];
            }
            if(i==2){
                arr1[i][j] = random[j+i+4];
            }
        }
    }
    std::vector<std::pair<int, int> > result;
    for (int p = 0; p<3; p++) {
        for (int m = 0; m<3; m++) {
            if (arr1[p][m]==0) {
                result.emplace_back(p, m);
            }
        }
    }
    for(std::vector<std::pair<int, int> >::iterator it = result.begin(); it != result.end(); it++){
        std::vector<std::pair<int, int>>::iterator x;
        zero_loc.first = it->first;
        zero_loc.second = it->second;
    }
}

void Matrix::show() const {
    for (int i = 0; i < 3; ++i) {
        std::cout << "| ";
        for (int j = 0; j < 3; ++j) {
            if(i==0) {
                if(random[j] == 0){
                    std::cout << "  | ";
                    continue;
                }
                std::cout << random[j] << " | ";
            }
            if(i==1) {
                if(random[j+3] == 0){
                    std::cout << "  | ";
                    continue;
                }
                std::cout << random[j + 3] << " | ";
            }
            if(i==2) {
                if(random[j+6] == 0){
                    std::cout << "  | ";
                    continue;
                }
                std::cout << random[j+6] << " | ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "____________________" << std::endl;
}

Matrix::~Matrix() {
}

Matrix Matrix::move(int num, bool verbose) {
    Matrix matrix{*this};
    auto iter = std::find(matrix.random.begin(), matrix.random.end(), num);
    auto zero = std::find(matrix.random.begin(), matrix.random.end(), 0);
    if(iter == random.end()){
        std::cout << "not found\n";
        return *this;
    }
    int arr[3][3];
    for(int i{0}; i < 3; i++){
        for(int j{0}; j < 3; j++){
            if(i==0) {
                arr[i][j] = random[j+i];
            }
            if(i==1){
                arr[i][j] = random[j+i+2];
            }
            if(i==2){
                arr[i][j] = random[j+i+4];
            }
        }
    }
    std::vector<std::pair<int, int> > result;
    for (int p{0}; p<3; p++) {
        for (int m{0}; m<3; m++) {
            if (num == arr[p][m]) {
                result.emplace_back(p, m);
            }
        }
    }
    for(std::vector<std::pair<int, int> >::iterator it = result.begin(); it != result.end(); it++){
        if(matrix.zero_loc.first != it->first && matrix.zero_loc.second != it->second){
            std::cout << "this number can not be moved!" << std::endl;
            return *this;
        }
        if(matrix.zero_loc.first == it->first && matrix.zero_loc.second != it->second && std::abs(matrix.zero_loc.second - it->second) != 1){
            std::cout << "this number can not be moved!" << std::endl;
            return *this;
        }
        if(matrix.zero_loc.first != it->first && matrix.zero_loc.second == it->second && std::abs(matrix.zero_loc.first - it->first) != 1){
            std::cout << "this number can not be moved!" << std::endl;
            return *this;
        }
    }
    for(std::vector<std::pair<int, int> >::iterator it = result.begin(); it != result.end(); it++){
        matrix.zero_loc.first = it->first;
        matrix.zero_loc.second = it->second;
    }
    std::swap(*iter, *zero);
    if(verbose){
        matrix.show();
    }
    return matrix;
}

void Matrix::set_random() {
    static std::vector<int> randoms{};
    int p[9] = {0,1,2,3,4,5,6,7,8};
    Matrix matrix1{goal};
    int k{0};
    int degree{rand() % 100};
    auto iter = std::find(randoms.begin(), randoms.end(), degree);
    while(iter != randoms.end()){
        degree = rand() % 100;
        iter = std::find(randoms.begin(), randoms.end(), degree);
    }
    Matrix matrix2;
    while(k < degree) {
        matrix2 = matrix1;
        int j{rand()%9};
        if(j%4 == 0){
            matrix1 = matrix1.moveRight();
            if(matrix2.isSame(matrix1)){
                k--;
            }
        }
        if(j%4 == 1){
            matrix1 = matrix1.moveLeft();
            if(matrix2.isSame(matrix1)){
                k--;
            }
        }
        if(j%4 == 2){
            matrix1 = matrix1.moveUp();
            if(matrix2.isSame(matrix1)){
                k--;
            }
        }
        if(j%4 == 3){
            matrix1 = matrix1.moveDown();
            if(matrix2.isSame(matrix1)){
                k--;
            }
        }
        k++;
    }
    for (int i=0; i<9; ++i){
        p[i] = matrix1.random[i];
    }
    if(random.size() == 9){
        for (int i=0; i<9; ++i){
            random[i] = p[i];
        }
    }
    if(random.empty()){
        for(int & i : p){
            random.push_back(i);
        }
    }
    if(goal.empty()){

    }
    int arr1[3][3];
    for(int i{0}; i < 3; i++){
        for(int j{0}; j < 3; j++){
            if(i==0) {
                arr1[i][j] = random[j+i];
            }
            if(i==1){
                arr1[i][j] = random[j+i+2];
            }
            if(i==2){
                arr1[i][j] = random[j+i+4];
            }
        }
    }
    std::vector<std::pair<int, int> > result;
    for (int p = 0; p<3; p++) {
        for (int m = 0; m<3; m++) {
            if (arr1[p][m]==0) {
                result.emplace_back(p, m);
            }
        }
    }
    for(std::vector<std::pair<int, int> >::iterator it = result.begin(); it != result.end(); it++){
        std::vector<std::pair<int, int>>::iterator x;
        zero_loc.first = it->first;
        zero_loc.second = it->second;
    }
}

void Matrix::set_goal(const std::vector<int> arr) {
    if(goal.empty()){
        for (int i = 0; i < 9; ++i) {
            goal.push_back(arr[i]);
        }
        return;
    }
    for (int i = 0; i < 9; ++i) {
        goal[i] = arr[i];
    }
}

void Matrix::show_goal() {
    for (int i = 0; i < 3; ++i) {
        std::cout << "| ";
        for (int j = 0; j < 3; ++j) {
            if(i==0) {
                if(goal[j] == 0){
                    std::cout << "  | ";
                    continue;
                }
                std::cout << goal[j] << " | ";
            }
            if(i==1) {
                if(goal[j+3] == 0){
                    std::cout << "  | ";
                    continue;
                }
                std::cout << goal[j + 3] << " | ";
            }
            if(i==2) {
                if(goal[j+6] == 0){
                    std::cout << "  | ";
                    continue;
                }
                std::cout << goal[j+6] << " | ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "____________________" << std::endl;
}

Matrix Matrix::moveRight(bool verbose) {
    int arr[3][3];
    for(int i{0}; i < 3; i++){
        for(int j{0}; j < 3; j++){
            if(i==0) {
                arr[i][j] = random[j+i];
            }
            if(i==1){
                arr[i][j] = random[j+i+2];
            }
            if(i==2){
                arr[i][j] = random[j+i+4];
            }
        }
    }
    Matrix matrix = *this;
    if(matrix.zero_loc.second != 2) {
        matrix = move(arr[matrix.zero_loc.first][matrix.zero_loc.second + 1], verbose);
    }
    return matrix;
}

Matrix Matrix::moveLeft(bool verbose) {
    int arr[3][3];
    for(int i{0}; i < 3; i++){
        for(int j{0}; j < 3; j++){
            if(i==0) {
                arr[i][j] = random[j+i];
            }
            if(i==1){
                arr[i][j] = random[j+i+2];
            }
            if(i==2){
                arr[i][j] = random[j+i+4];
            }
        }
    }
    Matrix matrix = *this;
    if(matrix.zero_loc.second != 0) {
        matrix = move(arr[matrix.zero_loc.first][matrix.zero_loc.second-1], verbose);
    }
    return matrix;
}

Matrix Matrix::moveUp(bool verbose) {
    int arr[3][3];
    for(int i{0}; i < 3; i++){
        for(int j{0}; j < 3; j++){
            if(i==0) {
                arr[i][j] = random[j+i];
            }
            if(i==1){
                arr[i][j] = random[j+i+2];
            }
            if(i==2){
                arr[i][j] = random[j+i+4];
            }
        }
    }
    Matrix matrix = *this;
    if(matrix.zero_loc.first != 0) {
        matrix = move(arr[matrix.zero_loc.first - 1][matrix.zero_loc.second], verbose);
    }
    return matrix;
}

Matrix Matrix::moveDown(bool verbose) {
    int arr[3][3];
    for(int i{0}; i < 3; i++){
        for(int j{0}; j < 3; j++){
            if(i==0) {
                arr[i][j] = random[j+i];
            }
            if(i==1){
                arr[i][j] = random[j+i+2];
            }
            if(i==2){
                arr[i][j] = random[j+i+4];
            }
        }
    }
    Matrix matrix = *this;
    if(matrix.zero_loc.first != 2) {
        matrix = move(arr[matrix.zero_loc.first + 1][matrix.zero_loc.second], verbose);
    }
    return matrix;
}

bool Matrix::operator==(const Matrix& matrix) const {
    bool isSame{true};
    for (int i = 0; i < 9; ++i) {
        if(matrix.random[i] != random[i]){
            isSame = false;
            break;
        }
    }
    return isSame;
}

std::vector<int> Matrix::getGoal() const {
    return goal;
}

bool Matrix::isSame(const Matrix &matrix) const {
    bool same{true};
    for (int i = 0; i < 9; ++i) {
        if(matrix.random[i] != random[i]){
            same = false;
            break;
        }
    }
    return same;
}

Matrix::Matrix(const Matrix &matrix) {
    if(random.empty()) {
        for (int i = 0; i < 9; ++i) {
            random.push_back(matrix.random[i]);
        }
        for (int i = 0; i < 9; ++i) {
            goal.push_back(matrix.goal[i]);
        }
    } else{
        for (int i = 0; i < 9; ++i) {
            random[i] = matrix.random[i];
        }
        for (int i = 0; i < 9; ++i) {
            goal[i] = matrix.goal[i];
        }
    }
    zero_loc.first = matrix.zero_loc.first;
    zero_loc.second = matrix.zero_loc.second;
}

Matrix::Matrix() {
    for (int i = 1; i < 9; ++i) {
        goal.push_back(i);
    }
    goal.push_back(0);
}

