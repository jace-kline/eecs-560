#include "./Node.h"

template <typename T>
Node<T>::Node(const T& entry) {
    obj = entry;
    next = nullptr;
}

template <typename T>
Node<T>::Node(const T& entry, Node<T>* nextPtr) {
    obj = entry; // Assume overloaded equality operator on type T
    next = nextPtr;
}

template <typename T>
Node<T>::Node(const Node<T>& other) {
    obj = other.obj;
    next = other.isLeaf() ? nullptr : new Node<T>(*other.next);
}

template <typename T>
Node<T>::~Node() {
    if(!isLeaf()) delete next;
}

template <typename T>
bool Node<T>::isLeaf() const {
    return(next == nullptr);
}

template <typename T>
int Node<T>::getLength() const {
    return(isLeaf() ? 1 : 1 + next->getLength());
}

template <typename T>
Node<T>* Node<T>::getEnd() {
    return(isLeaf() ? this : next->getEnd());
}

template <typename T>
Node<T>* Node<T>::nodeAt(int index) {
    if(index < 1) {
        throw(std::runtime_error("List index provided is too small. Method: 'nodeAt'.\n"));
    } else if(isLeaf() && index > 1) {
        throw(std::runtime_error("List index provided is too large. Method: 'nodeAt'.\n"));
    }

    return(index == 1 ? this : next->nodeAt(index - 1));
}

template <typename T>
T Node<T>::getItem() const {
    return obj;
}

template <typename T>
void Node<T>::setItem(const T& item) {
    obj = item;
}

template <typename T>
Node<T>* Node<T>::getNext() {
    return next;
}

template <typename T>
void Node<T>::setNext(Node<T>* nextPtr) {
    next = nextPtr;
}

template <typename T>
void Node<T>::removeDuplicates() {
    if(isLeaf()) return;
    next->removeDuplicates();

    Node<T>* p = this;
    Node<T>* t = next;
    while(t != nullptr) {
        if(t->obj == obj) {
            p->next = t->next;
            deleteNode(t);
            t = p->next;
        } else {
            p = t;
            t = t->next;
        }
    }
}

template <typename T>
bool Node<T>::contains(const T& entry) const {
    return(entry == obj ? true : (isLeaf() ? false : next->contains(entry)));
}

template <typename T>
Node<T>* Node<T>::nodeFromItem(const T& entry) {
    return(entry == obj ? this : (isLeaf() ? nullptr : next->nodeFromItem(entry)));
}

template <typename T>
void Node<T>::traverse(void (*eff)(const T& val)) {
    eff(obj);
    if(!isLeaf()) next->traverse(eff);
}

template <typename T>
void Node<T>::traversePrint(void (*printFunc)(const T& val), std::string delimitter) const {
    printFunc(obj);
    if(!isLeaf()) {
        std::cout << delimitter;
        next->traversePrint(printFunc, delimitter);
    }
}

template <typename T>
Node<T>* Node<T>::filter(bool (*p)(const T& obj)) {
    if(p(obj)) {
        return isLeaf() ? new Node<T>(obj, nullptr) : new Node<T>(obj, next->filter(p));
    }
    return isLeaf() ? nullptr : next->filter(p);
}

template <typename T>
void deleteNode(Node<T>* n) {
    n->setNext(nullptr);
    delete n;
    n = nullptr;
}

template <typename T>
template <typename R>
R Node<T>::fold(R (*func)(const T& curVal, R accum), R initVal) const {
    return func(obj, isLeaf() ? initVal : next->fold(func, initVal));
}

// template <typename T>
// template <typename R, typename V>
// R foldWithContext(R (*func)(const V& c, const T& currentObj, R accum), const V& contextObj, R initVal) const {
//     return func(contextObj, currentObj, isLeaf() ? initVal : next->foldWithContext(func, contextObj, initVal));
// }

//template class Node<int>; // instantiate type parameter as int upon complilation

template class Node<int>;
template class Node<WEdge>;