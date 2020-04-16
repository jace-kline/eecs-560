#include "Test.h"

test_result runTest(HeapType t, int n) {
    Heap h = Heap(t);
    float buildt, deletet;
    
    clock_t timer = clock();
    for(int i = 0; i < n; i++) {
        h.insert(rand());
    }
    timer = clock() - timer;
    buildt = ((double)timer)/((double)CLOCKS_PER_SEC);

    timer = clock();
    h.popMin();
    timer = clock() - timer;
    deletet = ((double)timer)/((double)CLOCKS_PER_SEC);

    return(test_result { n, buildt, deletet });
}

void runTests() {
    test_result leftist_results[5];
    test_result skew_results[5];

    // gather the results
    int i = 0;
    for(int n = 100000; n <= 500000; n += 100000) {
        leftist_results[i] = runTest(LEFTIST, n);
        skew_results[i] = runTest(SKEW, n);
        i++;
    }

    // print the results
    printTable(leftist_results, "Performance - Min Leftist Heap");
    std::cout << '\n';
    printTable(skew_results, "Performance - Min Skew Heap");
}

void printTable(test_result results[], std::string header) {
    std::cout << std::left << std::setw(6 * CELL_W + 10) << std::setfill('~') << header;
    std::cout << '\n';
    
    std::cout << "\n|";
    printCell<std::string>("Input Size:", CELL_W + 2);
    std::cout << '|';
    for(int i = 0; i < 5; i++) {
        printCell<int>(results[i].input_size, CELL_W);
        std::cout << '|'; 
    }

    std::cout << '\n';
    std::cout << std::setw(6 * CELL_W + 10) << std::setfill('_') << '_';
    std::cout << "\n|";
    printCell<std::string>("Build (s):", CELL_W + 2);
    std::cout << '|';
    for(int i = 0; i < 5; i++) {
        printCellFloat(results[i].build_time, CELL_W);
        std::cout << '|';
    }

    std::cout << '\n';
    std::cout << std::setw(6 * CELL_W + 10) << std::setfill('_') << '_';
    std::cout << "\n|";
    printCell<std::string>("Delete Min (s):", CELL_W + 2);
    std::cout << '|';
    for(int i = 0; i < 5; i++) {
        printCellFloat(results[i].delete_time, CELL_W);
        std::cout << '|';
    }
    std::cout << '\n';
}

template <typename T>
void printCell(const T& x, int width) {
    std::cout << std::left << std::setw(width) << std::setfill(' ') << x;
}

void printCellFloat(const double& x, int width) {
    std::cout << std::fixed << std::setprecision(7) << std::left << std::setw(width) << std::setfill(' ') << x;
}

template void printCell<std::string>(const std::string&, int);
template void printCell<int>(const int&, int);