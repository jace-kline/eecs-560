#include "./TableHandler.h"

UserTableHandler::UserTableHandler() :
    linear(11, hash, linearCollisionFunc, userToHashKey, isDuplicateUsername),
    quadratic(11, hash, quadraticCollisionFunc, userToHashKey, isDuplicateUsername) 
{}

UserTableHandler::~UserTableHandler() {}

void UserTableHandler::addUsersFromFile(std::string filename) {
    std::ifstream fs;
    std::string s1;
    char comma;
    std::string s2;
    fs.open(filename);
    while(fs.peek() != EOF) {
        fs >> s1;
        if(s1.at(s1.length() - 1) == ',') s1.pop_back();
        else fs >> comma;
        fs >> s2;
        if(s2.at(s2.length() - 1) == '\n') s2.pop_back();
        if(isValidUsername(s1) && isValidPassword(s2)) {
            User u = User {s1, s2};
            linear.insert(u);
            quadratic.insert(u);
        }
    }
    fs.close();
}

void UserTableHandler::linearOutputHeader() const {
    std::cout << "Linear Probing:\n";
    std::cout << "---------------\n\n";
}

void UserTableHandler::quadraticOutputHeader() const {
    std::cout << '\n';
    std::cout << "Quadratic Probing:\n";
    std::cout << "------------------\n\n";
}

void UserTableHandler::addUser(const User& u) {
    linear.insert(u);
    quadratic.insert(u);

    std::string msg = "User record successfully added.\n";
    linearOutputHeader();
    std::cout << msg;
    quadraticOutputHeader();
    std::cout << msg;
    std::cout << '\n';
}

void UserTableHandler::removeUser(const User& u) {
    std::string success = "User record successfully removed.";
    std::string fail = "User record not found. Hence, the record was not removed.";
    linearOutputHeader();
    std::cout << (linear.remove(u) ? success : fail) << "\n\n";
    quadraticOutputHeader();
    std::cout << (quadratic.remove(u) ? success : fail) << "\n\n";
}

void UserTableHandler::forgotPassword(std::string uname) const {
    linearOutputHeader();
    linear.traverseWithCondition<std::string>(isMatchingUsername, printUser, printNotFound, uname);

    quadraticOutputHeader();
    quadratic.traverseWithCondition<std::string>(isMatchingUsername, printUser, printNotFound, uname);
}

void UserTableHandler::forgotUsername(std::string pass) const {
    linearOutputHeader();
    linear.traverseWithCondition<std::string>(isMatchingPassword, printUser, printNotFound, pass);

    quadraticOutputHeader();
    quadratic.traverseWithCondition<std::string>(isMatchingPassword, printUser, printNotFound, pass);
}

void UserTableHandler::printUsers() const {
    linearOutputHeader();
    linear.print();

    quadraticOutputHeader();
    quadratic.print();
}

int linearCollisionFunc(int i) { return i; }

int quadraticCollisionFunc(int i) { return(i ^ 2);}

void printNotFound() {
    std::cout << "No users match the given data provided.\n";
}
