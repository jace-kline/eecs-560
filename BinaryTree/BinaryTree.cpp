#include "BinaryTree.h"

template <typename T>
BinaryTree<T>::BinaryTree() {
    root = nullptr;
}

template <typename T>
BinaryTree<T>::BinaryTree(Node<T>* r) {
    root = r;
}

template <typename T>
BinaryTree<T>::BinaryTree(const BinaryTree<T>& other) {
    root = (other.isEmpty() ? nullptr : new Node<T>(other.root));
}

template <typename T>
BinaryTree<T>::~BinaryTree() {
    if(root != nullptr) delete root;
}

template <typename T>
bool BinaryTree<T>::isEmpty() const {
    return(root == nullptr);
}

template <typename T>
int BinaryTree<T>::height() const {
    return(isEmpty() ? -1 : root.height());
}

template <typename T>
bool BinaryTree<T>::isFull() const {
    if(isEmpty()) return true;
    return(root.isFull());
}

template <typename T>
void BinaryTree<T>::add(const T& obj) {
    if(isEmpty()) root = new Node<T>(obj);
    else if(isFull()) {
        Node<T>* cur = root;
        while(true) {
            if(cur.isLeaf()) {
                cur.setLeft(new Node<T>(obj));
                return;
            }
            cur = cur.getLeft();
        }
    } else {
        
    }
}