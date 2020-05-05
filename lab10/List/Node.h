#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <stdexcept>
#include "../Graph/WEdge.h"

template <typename T>
class Node {
    private:
        T obj;
        Node<T>* next;

    public:
        Node(const T& entry);
        Node(const T& entry, Node<T>* nextPtr);
        Node(const Node<T>& other); //copy constructor will recursively make a deep copy on each node. We don't want double deletes.
        ~Node();
        bool isLeaf() const;
        int getLength() const;
        Node<T>* getEnd();
        Node<T>* nodeAt(int index);
        T getItem() const;
        void setItem(const T& item);
        Node<T>* getNext();
        void setNext(Node<T>* nextPtr);
        void removeDuplicates();
        bool contains(const T& entry) const;
        Node<T>* nodeFromItem(const T& entry);
        void traverse(void (*eff)(const T& val));
        void traversePrint(void (*printFunc)(const T& val), std::string delimitter) const;
        Node<T>* filter(bool (*p)(const T& obj));
        
        template <typename R>
        R fold(R (*func)(const T& curVal, R accum), R initVal) const;

        // template <typename R, typename V>
        // R foldWithContext(R (*func)(const V& c, const T& currentObj, R accum), const V& contextObj, R initVal) const;
};


// This function used to both nullify the node's next ptr and then delete the node
// CAREFUL: Ensure that you make something reference the node's initial next ptr before calling this, otherwise memory leak
template <typename T>
void deleteNode(Node<T>* n);

#endif
