#include "Node.h"

Node::Node(int x) : val(x), left(nullptr), right(nullptr), rank(1) {}

Node::Node(int x, Node* l, Node* r) : val(x), left(l), right(r) {
    rank = min(nodeRank(left), nodeRank(right)) + 1;
}

Node::Node(const Node& n) {
    val = n.val;
    left = n.left == nullptr ? nullptr : new Node(*n.left);
    right = n.right == nullptr ? nullptr : new Node(*n.right);
    rank = n.rank;
}

Node::~Node() {
    removeLeft();
    removeRight();
}

void Node::removeLeft() {
    if(left != nullptr) {
        delete left;
        left = nullptr;
        rank = 1;
    }
}

void Node::removeRight() {
    if(right != nullptr) {
        delete right;
        right = nullptr;
        rank = 1;
    }
}

void Node::detatchLeft() {
    left = nullptr;
}

void Node::detatchRight() {
    right = nullptr;
}

void Node::attachLeft(Node* n) {
    left = n;
    rank = min(nodeRank(left), nodeRank(right)) + 1;
}

void Node::attachRight(Node* n) {
    right = n;
    rank = min(nodeRank(left), nodeRank(right)) + 1;
}

void Node::swapChildren() {
    swapPtrs(left, right);
}

int Node::getVal() const { return val; }

int Node::getRank() const { return rank; }

Node* Node::getLeft() { return left; }

Node* Node::getRight() { return right; }

int nodeRank(Node* n) {
    return (n == nullptr ? 0 : n->getRank());
}

Node* mergeLeftist(Node* n1, Node* n2) {
    // Base case - if a pointer is null, return the other
    if(n1 == nullptr) return n2;
    else if(n2 == nullptr) return n1;

    // If needed, swap pointers to make n1 <= n2
    if(n1->getVal() > n2->getVal()) swapPtrs(n1, n2);

    // Main algorithm

    // recurse on right child, then reattach to right
    n1->attachRight(mergeLeftist(n1->getRight(), n2));

    // maintain leftist tree property
    if(nodeRank(n1->getLeft()) < nodeRank(n1->getRight())) {
        n1->swapChildren();
    }
    return n1;
}

Node* mergeSkew(Node* n1, Node* n2) {
    // Base case - if a pointer is null, return the other
    if(n1 == nullptr) return n2;
    else if(n2 == nullptr) return n1;

    // If needed, swap pointers to make n1 <= n2
    if(n1->getVal() > n2->getVal()) swapPtrs(n1, n2);

    // Main algorithm

    // Always swap children
    n1->swapChildren();

    // recurse on former right child, then reattach to left
    n1->attachLeft(mergeSkew(n1->getLeft(), n2));

    return n1;
}

void swapPtrs(Node*& n1, Node*& n2) {
    Node* tmp = n1;
    n1 = n2;
    n2 = tmp;
    tmp = nullptr;
}

void printLevelOrderNodes(Node* n) {
    for(int i = 0; i <= height(n); i++) {
        printLevelNodes(n, i);
    }
}

void printLevelNodes(Node* n, int i) {
    if(n == nullptr) return;
    else if(i == 0) std::cout << n->getVal() << ' ';
    else {
        printLevelNodes(n->getLeft(), i - 1);
        printLevelNodes(n->getRight(), i - 1);
    }
}

int height(Node* n) {
    if(n == nullptr) return -1;
    else return max(height(n->getLeft()), height(n->getRight())) + 1;
}

int max(int x, int y) {
    return x < y ? y : x;
}

int min(int x, int y) {
    return x < y ? x : y;
}
