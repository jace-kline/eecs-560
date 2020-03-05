#ifndef NODE_H
#define NODE_H

#include <stdexcept>

// Helper double-linked list class for inorder operations on BST Nodes
template <typename T>
class ListNode {
    public:
        T item;
        ListNode<T>* prev;
        ListNode<T>* next;
        ListNode<T>(const T& obj);
        ListNode<T>(const T& obj, ListNode<T>* p, ListNode<T>* n);
        ~ListNode<T>();
        T at(int i) const;
        ListNode<T>* head();
        ListNode<T>* last();
        // Assumption that repeated elements are adjacent
        ListNode<T>* kthUniqueItemPtr(int k);
        ListNode<T>* inorderSuccessorPtr(const T& obj);
};

// Type T must have <, >, <=, >=, == operators defined
template <typename T>
class Node {
    private:
        T item;
        Node<T>* left;
        Node<T>* right;

    protected:
        void doLevel(void (*eff)(const T&), int level) const;
        void doReverseLevel(void (*eff)(const T&), int level) const;
        int traverseLeftSideHelp(void (*eff)(const T&), int threshold) const;
        int traverseRightSideHelp(void (*eff)(const T&), int threshold) const;
        // void doLevelIfLeaf(void (*eff)(const T&), int level) const;
        Node<T>* removeHelper(Node<T>* target);
        ListNode<T>* inorderSuccessorHelp(const T& obj) const;
        ListNode<T>* toInorderListHelper() const;
        ListNode<T>* toInorderList() const;

    public:
        Node<T>(const T& obj);
        Node<T>(const T& obj, Node<T>* l, Node<T>* r);
        Node<T>(const Node<T>& other);
        ~Node<T>();
        
        bool isLeaf() const;
        int height() const;
        bool isFull() const;
        T getItem() const;
        Node<T>* getLeft();
        Node<T>* getRight();
        int numNodes() const;
        bool add(const T& obj);
        bool remove(const T& obj);

        // template <typename R>
        // bool anyNodesSatisfy(bool (*p)(Node<T>*, R), R);
        // bool contains(const T& obj) const;
        // bool containsWithRelation(bool (*relation)(const T&, const T&));
        // T popLastLeaf();
        // void combine(Node<T>* other);
        void setItem(const T& obj);
        void setLeft(Node<T>* l);
        void setRight(Node<T>* r);
        // Node<T>* rightmostLeaf();
        // void traversePreorder(void (*eff)(const T&)) const;
        // void traversePostorder(void (*eff)(const T&)) const;
        void traverseInorder(void (*eff)(const T&)) const;
        void traverseLevel(void (*eff)(const T&)) const;
        void traverseSpiralLevel(void (*eff)(const T&)) const;
        void traverseLeftSide(void (*eff)(const T&)) const;
        void traverseRightSide(void (*eff)(const T&)) const;
        // void traverseLeavesLevel(void (*eff)(const T&)) const;
        T inorderSuccessor(const T& obj); // Call this from the root
        T kthUniqueItem(int k) const;
};


#endif