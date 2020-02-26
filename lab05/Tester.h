#ifndef TESTER_H
#define TESTER_H

#include <stdlib.h>
#include <cmath>
#include <time.h>
#include <iostream>
#include <iomanip>
#include "IntHash.h"
#include "HashTable.h"

#define MAX_GEN_VAL 5000000
#define CELL_W 14

class Tester {
    private:

        double quadratic_time_results[5];
        int quadratic_find_results[5];

        double double_time_results[5];
        int double_find_results[5];
        

    protected:
        // void genNewSeed() const;
        int timeInputSize(int iter) const;
        int findInputSize(int iter) const;
        int genRandomInt() const;
        void runTest(int iter, bool is_quadratic);
        void printTable(bool is_quadratic);
        void runTests();
        void printResults();

    public:
        Tester();
        ~Tester();
        void run();
};

template <typename T>
void printCell(const T& x, int width);

void printCellFloat(const double& x, int width);

#endif