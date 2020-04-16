#include "Heap.h"

Heap::Heap(HeapType t) : top(nullptr), type(t) {}

Heap::~Heap() {
    if(top != nullptr) delete top;
    top = nullptr;
}

bool Heap::isEmpty() const {
    return top == nullptr;
}

void Heap::insert(int x) {
    Node* n = new Node(x);
    if(type == LEFTIST) top = mergeLeftist(top, n);
    else top = mergeSkew(top, n);
    n = nullptr;
}

int Heap::popMin() {
    if(isEmpty()) throw(std::runtime_error("Error. Attempted to delete from empty heap."));
    int x = top->getVal();

    // Assign top's children to be standalone nodes
    Node* l = top->getLeft();
    Node* r = top->getRight();

    // detach the min node from its children and delete it
    top->detatchLeft();
    top->detatchRight();
    delete top;
    top = nullptr;

    // run a merge on the two fromer children nodes
    if(type == LEFTIST) top = mergeLeftist(l, r);
    else top = mergeSkew(l, r);

    l = nullptr;
    r = nullptr;

    return x;
}

void Heap::printLevelOrder() const {
    if(!isEmpty()) printLevelOrderNodes(top);
    else std::cout << "The heap is empty.\n";
}