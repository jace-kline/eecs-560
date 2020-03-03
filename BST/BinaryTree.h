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
        bool add(const T& obj);

        // template <typename R>
        // bool anyNodesSatisfy(bool (*p)(Node<T>*, R), R);
        // bool contains(const T& obj) const;
        bool remove(const T& obj);
        // bool removeWithCondition(bool (*p)(const T&));
        // T popLastLeaf();
        int numNodes() const;
        // void traversePreorder(void (*eff)(const T&)) const;
        // void traversePostorder(void (*eff)(const T&)) const;
        void traverseInorder(void (*eff)(const T&)) const;
        void traverseLevel(void (*eff)(const T&)) const;
        // void traverseLeavesLevel(void (*eff)(const T&)) const;
};

#endif