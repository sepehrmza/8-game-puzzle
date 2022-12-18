#include "menu.h"

int main() {
    Menu menu{};
    Menu::welcome();
    int number{};
    std::cin >> number;
    menu.getter(number);
    menu.how_to_play();
    menu.automatic_solver();
    return 0;
}
