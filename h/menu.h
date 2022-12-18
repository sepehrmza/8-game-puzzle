//
// Created by Sepehr on 12/23/2020.
//

#ifndef MIDETERM_PROJECT_MENU_H
#define MIDETERM_PROJECT_MENU_H
#include "BFS.h"
#include "dfs.h"
#include "Bidirectional.h"

class Menu {
public:
    static void Color(int color){ SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color); }
    static void welcome();
    void getter(int number);
    void how_to_play();
    void automatic_solver();
private:
    Matrix matrix;
    std::string yesOrNo;
    std::string play_more;
};


#endif //MIDETERM_PROJECT_MENU_H
