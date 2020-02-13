#include "./HashTable.h"

template <typename T, typename K>
HashTable<T,K>::HashTable(int size, int (*hashFunc)(const K& key, int s), int (*collisionFunc)(int i), K (*objectToKeyFunc)(const T& obj)) {
    m = size;
    n = 0;
    arr = new Bucket<T>[m];
    hash = hashFunc;
    f = collisionFunc;
    objToKey = objectToKeyFunc;
}

template <typename T, typename K>
HashTable<T,K>::HashTable(const HashTable<T,K>& other) {
    m = other.m;
    n = other.n;
    arr = deepCopyArr(other.arr, m);
    hash = other.hash;
    f = other.f;
    objToKey = other.objToKey;
}

template <typename T, typename K>
HashTable<T,K>::~HashTable() {
    if(arr != nullptr) delete[] arr;
}

template <typename T, typename K>
int HashTable<T,K>::h_fromKey(K key) {
    return hash(key, m);
}

template <typename T, typename K>
int HashTable<T,K>::h(const T& obj) {
    return(h_fromKey(objToKey(obj)));
}

template <typename T, typename K>
int HashTable<T,K>::h_iter(const T& x, int i) {
    return((h(x) + f(i)) % m);
}

template <typename T, typename K>
int HashTable<T,K>::genIndex(const T& x) {
    int j;
    for(int i = 0; i < m; i++) {
        j = h_iter(x, i);
        if(arr[j].getItem() == x) return -1;
        if(arr[j].isEmpty()) return j;
    }
    return -1;
}

template <typename T, typename K>
bool HashTable<T,K>::contains(const T& obj) const {
    int j;
    for(int i = 0; i < m; i++) {
        j = h_iter(i);
        if(arr[j].isEmpty()) return false;
        else if(arr[j].getItem() == obj) return true;
    }
    return false;
}

template <typename T, typename K>
void HashTable<T,K>::insert(const T& obj) {
    if(loadFactor(n+1, m) > 0.5) rehash();
    int i = genIndex(obj);
    if(i == -1) return false;
    else {
        arr[i].setItem(obj);
        return true;
    }
}

template <typename T, typename K>
bool HashTable<T,K>::remove(const T& obj) {
    int j;
    for(int i = 0; i < m; i++) {
        j = h_iter(obj, i);
        if(arr[j].isEmpty()) return false;
        else if(arr[j].getItem() == obj) return(arr[j].removeItem());
    }
}

template <typename T, typename K>
void HashTable<T,K>::rehash() {
    HashTable<T,K> other = HashTable<T,K>(newSize(m), hash, f, objToKey);
    for(int i = 0; i < m; i++) {
        if(!arr[i].isEmpty()) other.insert(arr[i].getItem());
    }
    other.n = n;
    Bucket<T>* tmp = arr;
    *this = other; // Shallow copy
    if(tmp != nullptr) delete[] tmp;
}

float loadFactor(int n, int m) {
    return(n / m);
}

int newSize(int s) {
    return(nextPrime(s*2));
}

int nextPrime(int n) {
    return(isPrime(n) ? n : nextPrime(n+1));
}

bool isPrime(int n) {
    for(int d = 2; d < floor(n / 2); d++) {
        if(n % d == 0) return false;
    }
    return true;
}

template <typename R>
R* deepCopyArr(R* other, int size) {
    R* newArr = new R[size];
    for(int i = 0; i < size; i++) {
        newArr[i] = other[i];
    }
    return newArr;
}