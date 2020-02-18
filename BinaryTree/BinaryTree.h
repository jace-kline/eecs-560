#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "Node.h"

template <typename T>
class BinaryTree {
    private:
        Node<T>* root;

    public:
        BinaryTree<T>();
        BinaryTree<T>(Node<T>* r);
        BinaryTree<T>(const BinaryTree<T>& other);
        ~BinaryTree<T>();

        bool isEmpty() const;
        int height() const; // -1 if there is no root
        bool isFull() const;
        void add(const T& obj);
        bool remove(const T& obj);
        Node<T>* getRightmostLeaf();
        bool removeRightmostLeaf();
        void traversePreorder(void (*eff)(const T&)) const;
        void traversePostorder(void (*eff)(const T&)) const;
        void traverseInorder(void (*eff)(const T&)) const;
        void traverseLevel(void (*eff)(const T&)) const;
};

#endif