#ifndef NODE_H
#define NODE_H

#include <iostream>

class Node {
    private:
        int val;
        Node* left;
        Node* right;
        int rank;
    public:
        Node(int x);
        Node(int x, Node* l, Node* r);
        Node(const Node& n);
        ~Node();

        // Delete specified child's node recursively, then
        // points to null
        void removeLeft();
        void removeRight();

        // Unassigns the pointer for specified child
        // Will cause memory leak if not pointed to elsewhere
        void detatchLeft();
        void detatchRight();

        // Attach another node as a child to this node
        // Ensure memory is handled on former child node
        void attachLeft(Node* n);
        void attachRight(Node* n);

        void swapChildren();

        int getVal() const;
        int getRank() const;
        Node* getLeft();
        Node* getRight();
};

Node* mergeLeftist(Node* n1, Node* n2);
Node* mergeSkew(Node* n1, Node* n2);

void swapPtrs(Node*& n1, Node*& n2);
int nodeRank(Node* n);

void printLevelOrderNodes(Node* n);
void printLevelNodes(Node* n, int level);

int height(Node* n);

int max(int x, int y);
int min(int x, int y);

#endif