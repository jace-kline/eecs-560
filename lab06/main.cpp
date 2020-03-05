#include "Manager.h"

bool isGoodInput();
void displayMenu();
int promptResponse();

template <typename I>
I promptInput(std::string msg);

int main() {
    Manager m;
    m.constructFromFile();

    int code = 0;
    while(code != 9) {
        displayMenu();
        code = promptResponse();
        switch (code)
        {
        case 1: {
            m.addItem(promptInput<int>("Enter an integer to be added:\n> "));
            break;
        }
        case 2: {
            m.deleteItem(promptInput<int>("Enter an integer to be deleted:\n> "));
            break;
        }
        case 3: {
            m.inorderSuccessor(promptInput<int>("Enter an integer to find its inorder successor:\n> "));
            break;
        }
        case 4: {
            m.printLevelOrder();
            break;
        }
        case 5: {
            m.printSpiralLevelOrder();
            break;
        }
        case 6: {
            m.printLeftSideView();
            break;
        }
        case 7: {
            m.printRightSideView();
            break;
        }
        case 8: {
            m.kthSmallestItem(promptInput<int>("Enter an integer k to find the kth smallest item (no duplicates):\n> "));
            break;
        }
        case 9: {
            std::cout << "Ending program.\n";
            break;
        }
        default:
            std::cout << "Invalid choice. Input an integer from 1 to 9.\n";
            break;
        }
    }
    return 0;
}

void displayMenu() {
    std::cout << "\n\n1. Add Item\n"
              << "2. Delete Item\n"
              << "3. Inorder Successor\n"
              << "4. Level Order\n"
              << "5. Spiral Level Order\n"
              << "6. Left Side View\n"
              << "7. Right Side View\n"
              << "8. Kth Smallest Item\n"
              << "9. Exit\n\n";
}

int promptResponse() {
    int input = 0;
    std::cout << "> ";
    std::cin >> input;
    return input;
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