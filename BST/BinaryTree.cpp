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
    root = (other.isEmpty() ? nullptr : new Node<T>(*other.root));
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
    return(isEmpty() ? -1 : root->height());
}

template <typename T>
bool BinaryTree<T>::isFull() const {
    if(isEmpty()) return true;
    return(root->isFull());
}

template <typename T>
bool BinaryTree<T>::add(const T& obj) {
    if(isEmpty()) {
        root = new Node<T>(obj);
        return true;
    } else return(root->add(obj));
    return false;
}

template <typename T>
bool BinaryTree<T>::remove(const T& obj) {
    if(isEmpty()) return false;
    else if(obj == root->getItem()) {
        delete root;
        return true;
    }
    else return(root->remove(obj));
}

// template <typename T>
// template <typename R>
// bool BinaryTree<T>::anyNodesSatisfy(bool (*p)(Node<T>*, R), R x) {
//     if(isEmpty()) return false;
//     return root->anyNodesSatisfy(p, x);
// }

// template <typename T>
// T BinaryTree<T>::popLastLeaf() {
//     if(isEmpty()) throw(std::runtime_error("Error. Tried to pop an empty tree.\n"));
//     else if(root->isLeaf()) {
//         T val = root->getItem();
//         delete root;
//         root = nullptr;
//         return val;
//     }
//     else return(root->popLastLeaf());
// }

template <typename T>
int BinaryTree<T>::numNodes() const {
    return (isEmpty() ? 0 : root->numNodes());
}

// template <typename T>
// void BinaryTree<T>::traversePreorder(void (*eff)(const T&)) const {
//     if(!isEmpty()) root->traversePreorder(eff);
// }

// template <typename T>
// void BinaryTree<T>::traversePostorder(void (*eff)(const T&)) const {
//     if(!isEmpty()) root->traversePostorder(eff);
// }

template <typename T>
void BinaryTree<T>::traverseInorder(void (*eff)(const T&)) const {
    if(!isEmpty()) root->traverseInorder(eff);
}

template <typename T>
void BinaryTree<T>::traverseLevel(void (*eff)(const T&)) const {
    if(!isEmpty()) root->traverseLevel(eff);
}

template <typename T>
void BinaryTree<T>::traverseSpiralLevel(void (*eff)(const T&)) const {
    if(!isEmpty()) root->traverseSpiralLevel(eff);
}

// template <typename T>
// void BinaryTree<T>::traverseLeavesLevel(void (*eff)(const T&)) const {
//     if(!isEmpty()) root->traverseLeavesLevel(eff);
// }

template <typename T>
void BinaryTree<T>::traverseLeftSide(void (*eff)(const T&)) const {
    if(!isEmpty()) root->traverseLeftSide(eff);
}

template <typename T>
void BinaryTree<T>::traverseRightSide(void (*eff)(const T&)) const {
    if(!isEmpty()) root->traverseRightSide(eff);
}

template <typename T>
T BinaryTree<T>::inorderSuccessor(const T& obj) {
    if(isEmpty()) throw(std::runtime_error("Empty tree cannot return any value."));
    try {
        T succ = root->inorderSuccessor(obj);
        return succ;
    } catch(std::runtime_error& e) {
        throw(e);
    }
}

template <typename T>
T BinaryTree<T>::kthUniqueItem(int k) {
    if(isEmpty()) throw(std::runtime_error("Empty tree cannot return any value."));
    try {
        T x = root->kthUniqueItem(k);
        return x;
    } catch(std::runtime_error& e) {
        throw(e);
    }
}

template class BinaryTree<int>;