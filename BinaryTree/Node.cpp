#include "Node.h"

template <typename T>
Node<T>::Node(const T& obj) {
    item = obj; // Must overload equality for type T
    left = nullptr;
    right = nullptr;
}

template <typename T>
Node<T>::Node(const T& obj, Node<T>* l, Node<T>* r) {
    item = obj;
    // Recursively use the copy constructor on children nodes
    left = (l == nullptr ? nullptr : new Node<T>(*l));
    right = (r == nullptr ? nullptr : new Node<T>(*r));
}

template <typename T>
Node<T>::Node(const Node<T>& other) {
    item = other.item;
    left = (other.left == nullptr ? nullptr : new Node<T>(other.left));
    right = (other.right == nullptr ? nullptr : new Node<T>(other.right));
}

template <typename T>
Node<T>::~Node() {
    if(left != nullptr) delete left;
    if(right != nullptr) delete right;
}

template <typename T>
bool Node<T>::isLeaf() const {
    return (left == nullptr && right == nullptr);
}

template <typename T>
int Node<T>::height() const {
    if(isLeaf()) return 0;
    else {
        int lheight = (left == nullptr ? 0 : left.height());
        int rheight = (right == nullptr ? 0 : right.height());
        return(1 + max(lheight, rheight));
    }
}

template <typename T>
bool Node<T>::isFull() const {
    return(isLeaf() ? true : 
          (left == nullptr || right == nullptr ? false : 
          left.isFull() && right.isFull() && left.height() == right.height()));
}

template <typename T>
T Node<T>::getItem() const {
    return item;
}

template <typename T>
Node<T>* Node<T>::getLeft() {
    return left;
}

template <typename T>
Node<T>* Node<T>::getRight() {
    return right;
}

template <typename T>
void Node<T>::setItem(const T& obj) {
    item = obj;
}

template <typename T>
void Node<T>::setLeft(Node<T>* l) {
    if(left != nullptr) delete left;
    left = l;
}

template <typename T>
void Node<T>::setRight(Node<T>* r) {
    if(right != nullptr) delete right;
    right = r;
}

template <typename T>
void Node<T>::traversePreorder(void (*eff)(const T&)) const {
    eff(item);
    if(left != nullptr) left.traversePreorder(eff);
    if(right != nullptr) right.traversePreorder(eff);
}

template <typename T>
void Node<T>::traversePostorder(void (*eff)(const T&)) const {
    if(left != nullptr) left.traversePostorder(eff);
    if(right != nullptr) right.traversePostorder(eff);
    eff(item);
}

template <typename T>
void Node<T>::traverseInorder(void (*eff)(const T&)) const {
    if(left != nullptr) left.traverseInorder(eff);
    eff(item);
    if(right != nullptr) right.traverseInorder(eff);
}
