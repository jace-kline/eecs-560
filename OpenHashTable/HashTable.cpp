#include "./HashTable.h"

template<typename T, typename K>
HashTable<T,K>::HashTable(int size, K (*objToKeyFunc)(const T& obj), int (*hashFunc)(const K& key, int s)) {
    buckets = size;
    array = new ListInterface<T>[buckets];
    hash = hashFunc;
    objToKey = objToKeyFunc;
}

template<typename T, typename K>
HashTable<T,K>::HashTable(const HashTable<T,K>& other) {

}

template <typename T, typename K>
HashTable<T,K>::~HashTable() {
    if(array != nullptr) delete array;
}

template <typename T, typename K>
int HashTable<T,K>::hashFromObj(const T& obj) {
    return hash(objToKey(obj), buckets);
}