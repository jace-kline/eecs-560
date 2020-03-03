#ifndef NODE_H
#define NODE_H

#include <stdexcept>

// Type T must have <, >, <=, >=, == operators defined
template <typename T>
class Node {
    private:
        T item;
        Node<T>* left;
        Node<T>* right;

    protected:
        void doLevel(void (*eff)(const T&), int level) const;
        // void doLevelIfLeaf(void (*eff)(const T&), int level) const;
        Node<T>* removeHelper(Node<T>* target, bool parentOnLeft);
        Node<T>* successorNode() const;
        Node<T>* furthestLeftNode() const;

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
        // void traverseLeavesLevel(void (*eff)(const T&)) const;
};

#endif