#ifndef USER_H
#define USER_H

#include <string>

struct User {
    std::string username;
    std::string password;
};

bool operator==(const User& u1, const User& u2);
int hash(std::string uname, int size);
std::string userToHashKey(const User& u);
bool isValidUsername(std::string s);
bool isValidPassword(std::string s);
bool allLowercase(std::string s);

#endif