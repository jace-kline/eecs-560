#ifndef USER_TABLE_HANDLER_H
#define USER_TABLE_HANDLER_H

#include "./User.h"
#include "./HashTable.h"
#include <fstream>

class UserTableHandler {
    private:
        HashTable<User,std::string> linear;
        HashTable<User,std::string> quadratic;

    protected:
        void linearOutputHeader() const;
        void quadraticOutputHeader() const;
    
    public:
        UserTableHandler();
        ~UserTableHandler();
        void addUsersFromFile(std::string filename);
        void addUser(const User& u);
        void removeUser(const User& u);
        void forgotPassword(std::string uname) const;
        void forgotUsername(std::string pass) const;
        void printUsers() const;
};

int linearCollisionFunc(int i);
int quadraticCollisionFunc(int i);
void printNotFound();

#endif