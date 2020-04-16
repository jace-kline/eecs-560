#ifndef HEAP_H
#define HEAP_H

#include "Node.h"
#include <stdexcept>

enum HeapType {LEFTIST, SKEW};

class Heap {
    private:
        Node* top;
        HeapType type;

    public:
        Heap(HeapType t);
        ~Heap();

        bool isEmpty() const;
        void insert(int x);
        int popMin(); // throws exception if empty heap

        void printLevelOrder() const;
    
};

#endif