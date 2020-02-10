#ifndef HASH_TABLE_H
#define HASH_TABLE_H

// #include "./HashTableInterface.h"
#include "./List.h"
#include "./Player.h"

template <typename T, typename K>
class HashTable {
    private:
        int buckets;
        int elements;
        List<T>* array;
        K (*objToKey)(const T& obj);
        int (*hashFunc)(const K& key, int s);

    protected:
        int hashFromObj(const T& obj) const;
        int hashFromKey(const K& key) const;

    public:

        HashTable<T,K>(int size, K (*objToKey)(const T& obj), int (*hashFunc)(const K& key, int s));
        HashTable<T,K>(const HashTable<T,K>& other);
        ~HashTable<T,K>();

        bool containsObj(const T& val) const;

        bool insert(const T& val);

        bool remove(const T& val);

        int numBuckets() const;

        int numElements() const;

        float loadFactor() const;

        void traverseObjects(void (*eff)(const T& obj));

        // List<T> filter(bool (*p)(const T& obj));

        void printTable(void (*printFunc)(const T& val)) const;

        template <typename R>
        R fold(R (*func)(const T& obj, R accum), R initVal) const;

        // template <typename R, typename V>
        // R foldWithContext(R (*func)(const V& c, const T& currentObj, R accum), const V& contextObj, R initVal) const;
};

// #include "./HashTable.cpp"

#endif