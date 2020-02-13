#include "./User.h"

int hash(std::string uname, int size) {
    int sum = 0;
    for(int i = 0; i < uname.length(); i++) {
        sum += toAscii(uname.at(i));
    }
    return(sum % size);
}

std::string userToHashKey(const User& u) {
    return u.username;
}

bool isValidUsername(std::string s) {

}

bool isValidPassword(std::string s) {

}

int toAscii(char c) {
    
}