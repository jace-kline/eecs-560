#include "./User.h"

User& User::operator=(const User& other) {
    username = other.username;
    password = other.password;
    return *this;
}

std::ostream& operator<<(std::ostream& o, const User& u) {
    o << u.username << " : " << u.password;
    return o;
}

void printUser(const User& u) {
    std::cout << u << '\n';
}

bool operator==(const User& u1, const User& u2) {
    return(u1.username == u2.username && u1.password == u2.password);
}

int hash(const std::string& pass, int size) {
    int sum = 0;
    char c;
    for(int i = 0; i < pass.length(); i++) {
        c = pass.at(i);
        sum += (c >= 'a' && c <= 'z' ? c : (c >= '0' && c <= '9' ? c - '0' : 0));
    }
    return(sum % size);
}

std::string userToHashKey(const User& u) {
    return u.password;
}

bool isValidUsername(std::string s) {
    int len = s.length();
    return(len > 1 && len < 7 && allLowercase(s));
}

bool isValidPassword(std::string s) {
    char c;
    int len = s.length();
    int num_chars = 0;
    int num_nums = 0;
    if(len < 5 || len > 7) return false;
    for(int i = 0; i < s.length(); i++) {
        c = s.at(i);
        if(c >= '0' && c <= '9') num_nums++;
        else if(c >= 'a' && c <= 'z') num_chars++;
        else return false;
    }
    if(num_nums >= 2 && num_chars >= 3) return true;
    return false;
}

bool isMatchingUsername(const User& u, std::string uname) {
    return(u.username == uname);
}

bool isMatchingPassword(const User& u, std::string pass) {
    return(u.password == pass);
}

bool isDuplicateUsername(const User& u1, const User& u2) {
    return(u1.username == u2.username);
}

bool allLowercase(std::string s) {
    for(int i = 0; i < s.length(); i++) {
        if(s.at(i) < 'a' || s.at(i) > 'z') return false;
    }
    return true;
}