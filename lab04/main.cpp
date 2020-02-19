#include "TreeHandler.h"

bool isGoodInput();
void displayMenu();
int promptResponse();

template <typename I>
I promptInput(std::string msg);

std::string promptTitleInput();
float promptRatingInput();

int main() {
    TreeHandler handler;
    handler.fillTreeFromFile("data.txt");

    int code = 0;
    while(code != 11) {
        displayMenu();
        code = promptResponse();
        switch (code)
        {
        case 1: {
            handler.isFull();
            break;
        }
        case 2: {
            handler.addMovie(Movie {promptTitleInput(), promptRatingInput()});
            break;
        }
        case 3: {
            handler.removeLastMovie();
            break;
        }
        case 4: {
            handler.isTitleLeaf(promptTitleInput());
            break;
        }
        case 5: {
            handler.printLeaves();
            break;
        }
        case 6: {
            handler.printTreeHeight();
            break;
        }
        case 7: {
            handler.preorderRatings();
            break;
        }
        case 8: {
            handler.postorderRatings();
            break;
        }
        case 9: {
            handler.inorderRatings();
            break;
        }
        case 10: {
            handler.levelTitles();
            break;
        }
        case 11: {
            std::cout << "Ending program.\n";
            break;
        }
        default:
            std::cout << "Invalid choice. Input an integer from 1 to 6.\n";
            break;
        }
    }
    return 0;
}

void displayMenu() {
    std::cout << "\n\n1. Is Full\n"
              << "2. Add Movie\n"
              << "3. Remove Last Movie Leaf\n"
              << "4. Leaf\n"
              << "5. Print Leaves\n"
              << "6. Print Tree Height\n"
              << "7. Preorder\n"
              << "8. Postorder\n"
              << "9. Inorder\n"
              << "10. Level order\n"
              << "11. Exit\n\n";
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

std::string promptTitleInput() {
    return(promptInput<std::string>("Input a Movie Title:\n> "));
}

float promptRatingInput() {
    float r;
    while(true) {
        r = promptInput<float>("Input a Rating:\n> ");
        if(isValidRating(r)) return r;
        else std::cout << "Rating does not match criteria (0.0 - 5.0). Please try again.\n";
    }
}