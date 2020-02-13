#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>

struct User {
    std::string username;
    std::string password;

    User& operator=(const User& other);
};

std::ostream& operator<<(std::ostream& o, const User& u);
void printUser(const User& u);
bool operator==(const User& u1, const User& u2);
int hash(const std::string& uname, int size);
std::string userToHashKey(const User& u);
bool isValidUsername(std::string s);
bool isValidPassword(std::string s);
bool isMatchingUsername(const User& u, std::string uname);
bool isMatchingPassword(const User& u, std::string pass);
bool isDuplicateUsername(const User& u1, const User& u2);
bool allLowercase(std::string s);

#endif