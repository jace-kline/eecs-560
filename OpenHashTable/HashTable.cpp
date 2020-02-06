#include "./HashTable.h"
#include "../Utils.h"

template<typename T, typename K>
HashTable<T,K>::HashTable(int size, K (*objToKeyFunc)(const T& obj), int (*hashFunc)(const K& key, int s)) {
    buckets = size;
    array = new List<T>[buckets];
    hash = hashFunc;
    objToKey = objToKeyFunc;
}

template<typename T, typename K>
HashTable<T,K>::HashTable(const HashTable<T,K>& other) {
    buckets = other.buckets;
    array = deepCopyArr(other.array);
    hash = other.hash;
    objToKey = other.objToKey;
}

template <typename T, typename K>
HashTable<T,K>::~HashTable() {
    if(array != nullptr) delete array;
    array = nullptr;
}

template <typename T, typename K>
int HashTable<T,K>::hashFromObj(const T& obj) {
    return hash(objToKey(obj), buckets);
}

template <typename T, typename K>
bool HashTable<T,K>::containsObj(const T& obj) const {
    return(array[hashFromObj(obj)].contains(obj));
}

template <typename T, typename K>
bool HashTable<T,K>::insert(const T& val) {
    if(!containsObj(val)) {
        array[hashFromObj(val)].insertFront(val);
        return true;
    }
    return false;
}

template <typename T, typename K>
bool HashTable<T,K>::remove(const T& val) {
    return(array[hashFromObj(val)].removeObj(val));
}

template <typename T, typename K>
int HashTable<T,K>::numBuckets() const {
    return buckets;
}

template <typename T, typename K>
int HashTable<T,K>::numElements() const {
    int sum = 0;
    for(int i = 0; i < buckets; i++) {
        sum = sum + array[i].getLength();
    }
    return sum;
}
