#ifndef MANAGER_H
#define MANAGER_H

#include <fstream>
#include <iostream>
#include "BinaryTree.h"

class Manager {
    private:
        BinaryTree<int> tree;
    
    public:
        Manager();
        ~Manager();
        void constructFromFile();
        void addItem(int x);
        void deleteItem(int x);
        void inorderSuccessor(int x);
        void printLevelOrder();
        void printSpiralLevelOrder();
        void printLeftSideView();
        void printRightSideView();
        void kthSmallestItem(int k);
};

void printFunc(const int& x);

#endif