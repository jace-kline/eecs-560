#ifndef DS_HANDLER_H
#define DS_HANDLER_H

#include "DisjointSet/DSetCollection.h"
#include "IO.h"
#include <string>
#include <fstream>
#include <iostream>

class DSHandler {
    private:
        DSetCollection<int> dsets;

    public:
        DSHandler();
        ~DSHandler();

        void loadFromFile(std::string filename);
        void unionSets();
        void findRep();
        void pathCompress();
        void printPath();
};

void printElement(const int& x);
void printBridge();

#endif