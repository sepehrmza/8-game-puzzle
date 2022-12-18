//
// Created by Sepehr on 12/16/2020.
//

#ifndef MIDETERM_PROJECT_MATRIX_H
#define MIDETERM_PROJECT_MATRIX_H
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include<utility>
#include <iterator>
#include<vector>
#include <string>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include <cctype>
#include <sstream>
#include<stack>

class Matrix {
public:
    Matrix();
    Matrix(Matrix const &matrix);
    explicit Matrix(const std::vector<int>& arr);
    ~Matrix();
    void set_numbers(const std::vector<int>& arr);
    void show() const;
    Matrix move(int num, bool verbose=false);
    Matrix moveRight(bool verbose=false);
    Matrix moveLeft(bool verbose=false);
    Matrix moveUp(bool verbose=false);
    Matrix moveDown(bool verbose=false);
    std::vector<int> getGoal() const;
    bool operator==(const Matrix& matrix) const;
    bool isSame(const Matrix& matrix) const;
    void set_random();
    void set_goal(const std::vector<int> arr);
    void show_goal();
private:
    std::vector<int> random;
    std::pair<int, int> zero_loc;
    std::vector<int> goal;
};


#endif //MIDETERM_PROJECT_MATRIX_H
