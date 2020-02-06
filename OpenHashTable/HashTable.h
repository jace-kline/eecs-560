#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "./HashTableInterface.h"
#include "./List.h"

template <typename T, typename K>
class HashTable : HashTableInterface {
    private:
        int buckets;
        List<T>* array;
        K (*objToKey)(const T& obj);
        int (*hashFunc)(const K& key, int s);

    protected:
        int hashFromObj(const T& obj);

    public:

        HashTable(int size, K (*objToKey)(const T& obj), int (*hashFunc)(const K& key, int s));
        HashTable(const HashTable<T,K>& other);
        ~HashTable();

        bool containsObj(const T& val) const;

        bool insert(const T& val);

        bool remove(const T& val);

        int numBuckets() const;

        int numElements() const;
};

#endif