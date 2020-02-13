#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "./Bucket.h"
#include <cmath> // for the floor function
#include "./User.h"
#include <string>

template<typename T, typename K>
class HashTable {
    private:
        int m;
        int n;
        Bucket<T>* arr;
        int (*hash)(const K& key, int s);
        int (*f)(int i);
        K (*objToKey)(const T& obj);
        bool (*areDuplicates)(const T& obj1, const T& obj2);

    protected:
        int h_fromKey(K key);
        int h(const T& obj);
        int h_iter(const T& x, int i);

        // Iterates h_iter with incremented i argument
        // If finds an available spot for x, returns that index
        // Otherwise, returns -1 (can't find spot)
        int genIndex(const T& x);

    public:
        HashTable<T,K>(int size, 
                       int (*hashFunc)(const K& key, int s), 
                       int (*collisionFunc)(int i),
                       K (*objectToKeyFunc)(const T& obj),
                       bool (*dup)(const T& o1, const T& o2));
        HashTable<T,K>(const HashTable<T,K>& other);
        ~HashTable<T,K>();
        bool contains(const T& obj) const;
        void insert(const T& obj);
        bool remove(const T& obj);
        void rehash();
        void print() const;

        template <typename R>
        void traverseWithCondition(bool (*p)(const T&, R), 
                                   void (*eff)(const T&), 
                                   void (*ifnone)(),
                                   R) const;
};

float loadFactor(int n, int m);
int newSize(int s); //return the number of buckets for a rehashed array
int nextPrime(int n);
bool isPrime(int n);

template <typename R>
R* deepCopyArr(R* other, int size);


#endif