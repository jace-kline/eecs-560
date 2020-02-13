#ifndef USER_H
#define USER_H

#include <string>

struct User {
    std::string username;
    std::string password;
};

int hash(std::string uname, int size);
std::string userToHashKey(const User& u);
bool isValidUsername(std::string s);
bool isValidPassword(std::string s);
int toAscii(char c);

#endif