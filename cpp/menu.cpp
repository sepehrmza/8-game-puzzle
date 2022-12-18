//
// Created by Sepehr on 12/23/2020.
//

#include "menu.h"

void Menu::welcome() {
    Color(9);
    std::cout << "\n\n\nWelcome To PUZZLE 8 :))))\n\n\n" << std::endl;
    Color(13);
    std::cout << "Please Enter The Number: \n\n\n";
    Color(2);
    std::cout << "1. ";
    Color(7);
    std::cout << "Set Numbers On Your Own.\n\n";
    Color(2);
    std::cout << "2. ";
    Color(7);
    std::cout << "Set Random.\n\n";
}

void Menu::getter(int number) {
    if(number == 1){
        std::string rawInput;
        std::vector<int> numbers{};
        std::cout << "Please Enter Numbers (not separated):";
        std::cin >> rawInput;
        int num{0};
        for (int i = 0; i < 9; ++i) {
            num = (int)(rawInput[i] - '0');
            numbers.push_back(num);
        }
        Matrix mat{numbers};
        matrix = mat;
    }
    if(number == 2){
        Matrix mat;
        mat.set_random();
        matrix = mat;
    }
    matrix.show();
}

void Menu::how_to_play() {
    std::vector<int> goals{};
    std::string str{};
    std::cout << "Do You Want To Set Goal? Insert Y or N. \n";
    std::cin >> str;
    if(str == "Y"){
        std::string goal{};
        std::cout << "Please Enter Numbers (not separated):";
        std::cin >> goal;
        int num{0};
        for (int i = 0; i < 9; ++i) {
            num = (int)(goal[i] - '0');
            goals.push_back(num);
        }
        matrix.set_goal(goals);
        matrix.show_goal();
    }
    Color(2);
    std::cout << "Do You Want To Play On Your Own? Insert Y or N. \n";
    std::string yes_or_no;
    std::cin >> yes_or_no;
    int num{};
    if(yes_or_no == "Y"){
        std::cout << "Here Is Your Puzzle And Your Goal:\n";
        std::cout << "Puzzle:\n";
        matrix.show();
        std::cout << "Goal:\n";
        matrix.show_goal();
        std::cout << "Start Playing! Please Insert The Number You Want To Move...\nIf You Want To Exit The Game Please Insert -1 .\n";
        Matrix goalMatrix{matrix.getGoal()};
        while(!matrix.isSame(goalMatrix)){
            std::cin >> num;
            if(num == -1){
                //std::cout << "Thanks For Playing.";
                return;
            }
            matrix = matrix.move(num, true);
        }
        std::cout << "Good Job :)))))" << std::endl;
        std::cout << "Do You Want To Play Again? " << std::endl;
        std::cin >> yesOrNo;
        return;
    }
    yesOrNo = "N";
}

void Menu::automatic_solver() {
    if(yesOrNo == "N"){
        int choose_algorithm{};
        std::cout << "With Which Algorithm Do You Want To Solve This Puzzle ? Choose The Number Please...\n";
        Color(2);
        std::cout << "1. ";
        Color(7);
        std::cout << "BFS" << std::endl;
        Color(2);
        std::cout << "2. ";
        Color(7);
        std::cout << "DFS" << std::endl;
        Color(2);
        std::cout << "3. ";
        Color(7);
        std::cout << "Bidirectional Search" << std::endl;
        std::cin >> choose_algorithm;
        std::cout << "Please Wait.... We Are Trying To Find The Best Solution For You! ;)) \n";
        if(choose_algorithm == 1) {
            int depth{};
            std::cout << "Please Enter Depth : " << std::endl;
            std::cin >> depth;
            BFS bfs;
            std::cout << "Here Is Your Solution:\n";
            clock_t tStart = clock();
            bfs.createTree(matrix, depth);
            bfs.show_solution();
            std::cout << "time of solving = ";
            std::cout << (double)(clock() - tStart)/CLOCKS_PER_SEC << " seconds" << std::endl;
        }
        if(choose_algorithm == 2){
            int depth{};
            std::cout << "Please Enter Depth : " << std::endl;
            std::cin >> depth;
            DFS dfs;
            std::cout << "Here Is Your Solution:\n";
            clock_t tStart = clock();
            dfs.createTree(matrix, depth);
            dfs.show_solution();
            std::cout << "time of solving = ";
            std::cout << (double)(clock() - tStart)/CLOCKS_PER_SEC << " seconds" << std::endl;
        }
        if(choose_algorithm == 3){
            std::cout << "Here Is Your Solution:\n";
            clock_t tStart = clock();
            Bidirectional b{};
            b.createTree(matrix);
            b.show_solution();
            std::cout << "time of solving = ";
            std::cout << (double)(clock() - tStart)/CLOCKS_PER_SEC << " seconds" << std::endl;
        }
    }
    std::cout << "Thanks For Playing.\n Do you Want To Play Again? Insert Y Or N.\n";
    std::cin >> play_more;
    if(play_more == "Y"){
        welcome();
        int number{};
        std::cin >> number;
        getter(number);
        how_to_play();
        automatic_solver();
    } else{
        std::cout << "Good Bye :))))))" << std::endl;
    }
}


