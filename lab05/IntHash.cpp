#include "IntHash.h"

int hash(const int& x, int s) {
    return(x % s);
}

int f_doubleHash(const int& x, int i) {
    return(i * (R - (x % R)));
}

int f_quadraticHash(const int& x, int i) {
    return(i * i);
}

int objToKey(const int& x) {
    return x;
}

bool areDuplicates(const int& x1, const int& x2) {
    return(x1 == x2);
}