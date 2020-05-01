#include "DSetCollection.h"

template <typename T>
DSetCollection<T>::DSetCollection(int size) {
    max_size = size;
    n = 0;
    ptrs = new DNode<T>*[max_size];
}

template <typename T>
DSetCollection<T>::~DSetCollection() {
    for(int i = 0; i < n; i++) {
        if(ptrs[i] != nullptr) delete ptrs[i];
    }
    delete[] ptrs;
}

template <typename T>
DNode<T>* DSetCollection<T>::nodeOfItem(const T& x) {
    for(int i = 0; i < n; i++) {
        if(ptrs[i] != nullptr && ptrs[i]->item == x) {
            return ptrs[i];
        }
    }
    return nullptr;
}

template <typename T>
int DSetCollection<T>::rankOfSet(const T& x) {
    DNode<T>* rep = nodeOfItem(x);
    if(rep == nullptr) return -1;
    else rep = rep->repr();

    int rank = 0;
    for(int i = 0; i < n; i++) {
        if(ptrs[i] != nullptr && ptrs[i]->repr() == rep) {
            if(ptrs[i]->depth() > rank) rank = ptrs[i]->depth();
        }
    }
    return rank;
}

template <typename T>
bool DSetCollection<T>::initSingleton(const T& x) {
    if(nodeOfItem(x) == nullptr && n < max_size) {
        ptrs[n] = new DNode<T>(x);
        n++;
        return true;
    }
    return false;
}

template <typename T>
const T& DSetCollection<T>::mkUnion(const T& x, const T& y) {
    DNode<T>* left;
    DNode<T>* right;
    try {
        left = nodeOfItem(findRepr(x));
        right = nodeOfItem(findRepr(y));

        if(rankOfSet(x) > rankOfSet(y)) {
            right->parent = left;
            return left->item;
        }
        else {
            left->parent = right;
            return right->item;
        }
    } catch(const T& e) {
        throw e;
    }
}

template <typename T>
const T& DSetCollection<T>::findRepr(const T& x) {
    DNode<T>* ptr = nodeOfItem(x);
    if(ptr == nullptr) throw x;
    else return ptr->repr()->item;
}

template <typename T>
bool DSetCollection<T>::pathCompress(const T& x) {
    DNode<T>* node = nodeOfItem(x);
    if(node == nullptr) return false;
    node->compress();
    return true;
}

template <typename T>
bool DSetCollection<T>::traversePath(const T& x, void (*eff)(const T&), void (*bridge)()) {
    DNode<T>* node = nodeOfItem(x);
    if(node == nullptr) return false;

    while(true) {
        eff(node->item);
        if(node->isRepr()) break;
        else bridge();
        node = node->parent;
    }
    return true;
}

template class DSetCollection<int>;