#ifndef DNODE_H
#define DNODE_H

template <typename T>
struct DNode {
    T item;
    DNode<T>* parent;

    // For creating new node. parent ptr points to itself.
    DNode<T>(T obj);

    // Destructor -> does NOT recursively delete parent
    ~DNode<T>();

    // Is the representative node of a disjoint set?
    bool isRepr();

    // Gets the representative node of this disjoint set
    DNode<T>* repr();

    // Path Compress -> makes parent ptr point to root
    void compress();

    int depth();
    
};

#endif