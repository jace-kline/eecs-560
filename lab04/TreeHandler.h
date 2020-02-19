#ifndef TREE_HANDLER_H
#define TREE_HANDLER_H

#include "BinaryTree.h"
#include <iostream>
#include <fstream>

class TreeHandler {
    private:
        BinaryTree<Movie> tree;
    
    public:
        TreeHandler();
        ~TreeHandler();
        void fillTreeFromFile(std::string filename);
        void isFull() const;
        void addMovie(const Movie& m);
        void removeLastMovie();
        void isTitleLeaf(std::string title);
        void printLeaves() const;
        void printTreeHeight() const;
        void preorderRatings() const;
        void postorderRatings() const;
        void inorderRatings() const;
        void levelTitles() const;
};

bool isLeafFunc(Node<Movie>* n, std::string title);
void printTitle(const Movie& m);
void printRating(const Movie& m);

#endif