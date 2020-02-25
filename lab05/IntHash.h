#ifndef INT_HASH_H
#define INT_HASH_H

#define M 1000003
#define R 773

int hash(const int& x, int s);

int f_doubleHash(const int& x, int i);

int f_quadraticHash(const int& x, int i);

int objToKey(const int& x);

bool areDuplicates(const int& x1, const int& x2);



#endif