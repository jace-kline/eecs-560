#include "./HashTable.h"
#include <iomanip>

template <typename T, typename K>
HashTable<T,K>::HashTable(int size, int (*hashFunc)(const K& key, int s), int (*collisionFunc)(int i), K (*objectToKeyFunc)(const T& obj), bool (*d)(const T& o1, const T& o2)) {
    m = size;
    const int m_ = m;
    n = 0;
    arr = new Bucket<T>[m_];
    hash = hashFunc;
    f = collisionFunc;
    objToKey = objectToKeyFunc;
    areDuplicates = d;
}

template <typename T, typename K>
HashTable<T,K>::HashTable(const HashTable<T,K>& other) {
    m = other.m;
    n = other.n;
    arr = deepCopyArr(other.arr, m);
    hash = other.hash;
    f = other.f;
    objToKey = other.objToKey;
    areDuplicates = other.areDuplicates;
}

template <typename T, typename K>
HashTable<T,K>::~HashTable() {
    if(arr != nullptr) delete[] arr;
}

template <typename T, typename K>
int HashTable<T,K>::h_fromKey(K key) const {
    return hash(key, m);
}

template <typename T, typename K>
int HashTable<T,K>::h(const T& obj) const {
    return(h_fromKey(objToKey(obj)));
}

template <typename T, typename K>
int HashTable<T,K>::h_iter(const T& x, int i) const {
    return((h(x) + f(i)) % m);
}

template <typename T, typename K>
int HashTable<T,K>::genIndex(const T& x) const {
    int j = 0;
    for(int i = 0; i < m; i++) {
        j = h_iter(x, i);
        if(arr[j].isEmpty()) return j;
        else if(areDuplicates(arr[j].getItem(), x)) return -1;
    }
    return -1;
}

template <typename T, typename K>
void HashTable<T,K>::overwriteWith(HashTable<T,K>* other) {
    Bucket<T>* tmp = arr;
    arr = other->arr;
    n = other->n;
    m = other->m;
    hash = other->hash;
    f = other->f;
    objToKey = other->objToKey;
    areDuplicates = other->areDuplicates;
    if(tmp != nullptr) delete[] tmp;
    other->arr = nullptr;
    delete other;
}

template <typename T, typename K>
bool HashTable<T,K>::existsDuplicate(const T& obj) const {
    for(int i = 0; i < m; i++) {
        if(!arr[i].isEmpty()) {
            if(areDuplicates(obj, arr[i].getItem())) return true;
        }
    }
    return false;
}

template <typename T, typename K>
bool HashTable<T,K>::contains(const T& obj) const {
    int j;
    for(int i = 0; i < m; i++) {
        j = h_iter(obj, i);
        if(arr[j].isEmpty() && !(arr[j].wasDeleted())) return false;
        else if(arr[j].getItem() == obj) return true;
    }
    return false;
}

template <typename T, typename K>
bool HashTable<T,K>::insert(const T& obj) {
    if(existsDuplicate(obj)) return false;
    if(((float)n / (float)m) > 0.5) {
        rehash();
    }
    int i = genIndex(obj);
    if(i == -1) return false;
    else {
        bool r = arr[i].setItem(obj);
        if(r) n++;
        return r;
    }
}

template <typename T, typename K>
bool HashTable<T,K>::remove(const T& obj) {
    int j;
    for(int i = 0; i < m; i++) {
        j = h_iter(obj, i);
        if(arr[j].isEmpty() && !(arr[j].wasDeleted())) return false;
        else if(arr[j].getItem() == obj) return(arr[j].removeItem());
    }
    return false;
}

template <typename T, typename K>
void HashTable<T,K>::rehash() {
    std::cout << "\nREHASH OCCURRED\n";
    HashTable<T,K>* other = new HashTable<T,K>(newSize(m), hash, f, objToKey, areDuplicates);
    for(int i = 0; i < m; i++) {
        if(!arr[i].isEmpty()) other->insert(arr[i].getItem());
    }
    overwriteWith(other);
}

template <typename T, typename K>
void HashTable<T,K>::print() const {
    for(int i = 0; i < m; i++) {
        std::cout << i << ": ";
        if(!arr[i].isEmpty()) std::cout << arr[i].getItem();
        std::cout << '\n';
    }
}

template <typename T, typename K>
template <typename R>
void HashTable<T,K>::traverseWithCondition(bool (*p)(const T&, R), 
                                   void (*eff)(const T&), 
                                   void (*ifnone)(),
                                   R x) const
{
    bool hit = false;
    for(int i = 0; i < m; i++) {
        if(p(arr[i].getItem(), x)) {
            eff(arr[i].getItem());
            hit = true;
        }
    }
    if(!hit) ifnone();
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

template class HashTable<User, std::string>;
template void HashTable<User, std::string>::traverseWithCondition<std::string>(bool (*p)(const User&, std::string), 
                                   void (*eff)(const User&), 
                                   void (*ifnone)(),
                                   std::string) const;
template Bucket<User>* deepCopyArr(Bucket<User>*, int);