#ifndef TEST_H
#define TEST_H

#include "Heap.h"
#include <iostream>
#include <iomanip>

#define CELL_W 14

struct test_result {
    int input_size;
    double build_time;
    double delete_time;
};

test_result runTest(HeapType t, int n);
void runTests();
void printTable(test_result results[], std::string header);

template <typename T>
void printCell(const T& x, int width);

void printCellFloat(const double& x, int width);

#endif