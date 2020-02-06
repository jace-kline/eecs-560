#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "./HashTableInterface.h"
#include "./ListInterface.h"

template <typename T, typename K>
class HashTable : HashTableInterface {
    private:
        int buckets;
        ListInterface<T>* array;
        K (*objToKey)(const T& obj);
        int (*hashFunc)(const K& key, int s);

    protected:
        int hashFromObj(const T& obj);

    public:

        HashTable(int size, K (*objToKey)(const T& obj), int (*hashFunc)(const K& key, int s));
        HashTable(const HashTable<T,K>& other);
        ~HashTable();

        bool contains(const T& val);

        bool insert(const T& val);

        bool remove(const T& val);

        int numBuckets();

        int numElements();
};

#endif