
#include "./HashTable.h"

template <typename T>
T* deepCopyArr(T* other, int size) {
    T* newArr = new T[size];
    for(int i = 0; i < size; i++) {
        newArr[i] = other[i];
    }
    return newArr;
}

template<typename T, typename K>
HashTable<T,K>::HashTable(int size, K (*objToKeyFunc)(const T& obj), int (*hashFunc)(const K& key, int s)) {
    this->buckets = size;
    this->array = new List<T>[buckets];
    this->hashFunc = hashFunc;
    this->objToKey = objToKeyFunc;
}

template<typename T, typename K>
HashTable<T,K>::HashTable(const HashTable<T,K>& other) {
    this->buckets = other.buckets;
    this->array = deepCopyArr(other.array, other.buckets);
    this->hashFunc = other.hashFunc;
    this->objToKey = other.objToKey;
}

template <typename T, typename K>
HashTable<T,K>::~HashTable() {
    if(array != nullptr) delete array;
    array = nullptr;
}

template <typename T, typename K>
int HashTable<T,K>::hashFromObj(const T& obj) const {
    return hashFunc(objToKey(obj), buckets);
}

template <typename T, typename K>
int HashTable<T,K>::hashFromKey(const K& key) const {
    return hashFunc(key, buckets);
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
    return( elements / buckets );
}

template <typename T, typename K>
List<T> HashTable<T,K>::filter(bool (*p)(const T& obj)) {
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
        array[i].traversePrint(printFunc, " -> ");
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

// template <typename T, typename K>
// template <typename R, typename V>
// R HashTable<T,K>::foldWithContext(R (*func)(const V& cont, const T& obj, R accum), const V& contextObj, R initVal) const {
//     R acc = initVal;
//     for(int i = buckets - 1; i >= 0; i--) {
//         acc = array[i].foldWithContext(func, contextObj, acc);
//     }
//     return acc;
// }

template class HashTable<Player,int>;
template bool HashTable<Player,int>::fold(bool (*)(const Player&, bool), bool) const;