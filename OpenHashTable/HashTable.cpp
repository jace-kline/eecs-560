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
        elements++;
        return true;
    }
    return false;
}

template <typename T, typename K>
bool HashTable<T,K>::remove(const T& val) {
    if(array[hashFromObj(val)].removeObj(val)) {
        elements--;
        return true;
    }
    return false;
}

template <typename T, typename K>
int HashTable<T,K>::numBuckets() const {
    return buckets;
}

template <typename T, typename K>
int HashTable<T,K>::numElements() const {
    return elements;
}

template <typename T, typename K>
float HashTable<T,K>::loadFactor() const {
    return( elements / size );
}

template <typename T, typename K>
List<T> filter(bool (*p)(const T& obj)) {
    List<T> l;
    for(int i = 0; i < buckets; i++) {
        l.combine(array[i].filter(p));
    }
    return l;
}

template <typename T, typename K>
void HashTable<T,K>::printTable(void (*printFunc)(const T& val)) const {
    for(int i=0; i < buckets; i++) {
        std::cout << i << ": -> ";
        array[i].printTraverse(printFunc, " -> ");
        std::cout << '\n';
    }
}

template <typename T, typename K>
template <typename R>
R HashTable<T,K>::fold(R (*func)(const T& obj, R accum), R initVal) const {
    R acc = initVal;
    for(int i = buckets - 1; i >= 0; i--) {
        acc = array[i].fold(func, acc);
    }
    return acc;
}

template <typename T, typename K>
template <typename R, typename V>
R HashTable<T,K>::foldWithContext(R (*func)(const V& cont, const T& obj, R accum), const V& contextObj, R initVal) const {
    R acc = initVal;
    for(int i = buckets - 1; i >= 0; i--) {
        acc = array[i].foldWithContext(func, contextObj, acc);
    }
    return acc;
}
