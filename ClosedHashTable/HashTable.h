#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "./Bucket.h"

template<typename T, typename K>
class HashTable {
    private:
        int m;
        int n;
        Bucket<T>* arr;
        int (*hash)(const K& key, int s);
        int (*f)(int i);
        K (*objToKey)(const T& obj);

    protected:
        int h_fromKey(K key);
        int h(const T& obj);
        int h_iter(const T& x, int i);

        // Iterates h_iter with incremented i argument
        // If finds an available spot for x, returns that index
        // Otherwise, returns -1 (can't find spot)
        int genIndex(const T& x);

        // Creates an entirely new hash table object
        HashTable<T,K> rehashImmutable();
        bool needsRehash() const;

    private:
        HashTable<T,K>(int size, 
                       int (*hashFunc)(const K& key, int s), 
                       int (*collisionFunc)(int i),
                       K (*objectToKeyFunc)(const T& obj));
        HashTable<T,K>(const HashTable<T,K>& other);
        ~HashTable<T,K>();
        float loadFactor() const;
        bool contains(const T& obj) const;
        bool insert(const T& obj);
        bool remove(const T& obj);
        void rehash();
        HashTable<T,K>& operator=(const HashTable<T,K>& other);
};

#endif