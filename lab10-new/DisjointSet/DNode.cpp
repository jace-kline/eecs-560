#include "DNode.h"

template <typename T>
DNode<T>::DNode(T obj) {
    item = obj;
    parent = this;
}

template <typename T>
DNode<T>::~DNode() {
    parent = nullptr;
}

template <typename T>
bool DNode<T>::isRepr() {
    return (parent == this);
}

template <typename T>
DNode<T>* DNode<T>::repr() {
    if(isRepr()) return this;
    else return parent->repr();
}

template <typename T>
void DNode<T>::compress() {
    if(!isRepr()) {
        parent->compress();
        parent = repr();
    }
    parent = repr();
}

template <typename T>
int DNode<T>::depth() {
    if(isRepr()) return 0;
    else return(parent->depth() + 1);
}

template class DNode<int>;
template class DNode<WEdge>;