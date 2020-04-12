#include "IO.h"

int promptBoundedInt(std::string msg, int low = INT32_MIN, int high = INT32_MAX);

std::ostream& operator<<(std::ostream& os, const Game& g) {
    os << g.name << ',' << g.downloads;
    return os;
}

int promptResponse() {
    return promptBoundedInt("> ", 1);
}

bool isGoodInput() {
    if(std::cin.fail()) {
        std::cout.clear();
        std::cin.ignore();
        return false;
    }
    return true;
}

template <typename I>
I promptInput(std::string msg) {
    I x;
    while(true) {
        std::cout << msg;
        std::cin >> x;
        if(isGoodInput()) return x;
        else std::cout << "Invalid input. Please try again.\n";
    }
}

int promptBoundedInt(std::string msg, int low, int high) {
    int input = -1;
    while(true) {
        input = promptInput<int>(msg);
        if(input < low) std::cout << "Input value too low. Please try again.\n";
        else if(input > high) std::cout << "Input value too high. Please try again.\n";
        else break;
    }
    return input;
}

Game promptGameInput() {
    std::string name = promptInput<std::string>("Enter the game name:\n> ");
    int downloads = promptBoundedInt("Enter the number of downloads for this game (in thousands):\n> ", 0);
    return (Game { name, downloads });
}