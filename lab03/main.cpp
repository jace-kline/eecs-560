#include "./TableHandler.h"

bool isGoodInput();
void displayMenu();
int promptResponse();

template <typename I>
I promptInput(std::string msg);

std::string promptUsernameInput();
std::string promptPasswordInput();

int main() {
    UserTableHandler handler;
    handler.addUsersFromFile("data.txt");

    int code = 0;
    while(code != 6) {
        displayMenu();
        code = promptResponse();
        switch (code)
        {
        case 1: {
            handler.addUser(User {promptUsernameInput(), promptPasswordInput()});
            break;
        }
        case 2: {
            handler.removeUser(User {promptUsernameInput(), promptPasswordInput()});
            break;
        }
        case 3: {
            handler.forgotPassword(promptUsernameInput());
            break;
        }
        case 4: {
            handler.forgotUsername(promptPasswordInput());
            break;
        }
        case 5: {
            handler.printUsers();
            break;
        }
        case 6: {
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
    std::cout << "\n\n1. Add User\n"
              << "2. Remove User\n"
              << "3. Forgot Password\n"
              << "4. Forgot Username\n"
              << "5. Print Users\n"
              << "6. Exit\n\n";
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

std::string promptUsernameInput() {
    std::string uname;
    while(true) {
        uname = promptInput<std::string>("Input a Username:\n> ");
        if(isValidUsername(uname)) return uname;
        else std::cout << "Username does not match criteria. Please try again.\n";
    }
}

std::string promptPasswordInput() {
    std::string pass;
    while(true) {
        pass = promptInput<std::string>("Input a Password:\n> ");
        if(isValidPassword(pass)) return pass;
        else std::cout << "Password does not match criteria. Please try again.\n";
    }
}