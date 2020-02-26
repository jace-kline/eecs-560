#include "Tester.h"

Tester::Tester() {
    for(int i = 0; i < 5; i++) {
        quadratic_time_results[i] = 0.0;
        quadratic_find_results[i] = 0;
        double_time_results[i] = 0.0;
        double_find_results[i] = 0;
    }
}
Tester::~Tester() {}

// void Tester::genNewSeed() const {
//     srand(time(NULL));
// }

int Tester::timeInputSize(int iter) const {
    return(floor(M * ((float)(iter + 1) / 10.0)));
}

int Tester::findInputSize(int iter) const {
    return(floor(M * ((float)(iter + 1) / 100.0)));
}

int Tester::genRandomInt() const {
    return((rand() % MAX_GEN_VAL) + 1);
}

void Tester::runTest(int iter, bool is_quadratic) {
    HashTable<int,int> ht(M, 
                          hash, 
                          (is_quadratic ? f_quadraticHash : f_doubleHash),
                          objToKey,
                          areDuplicates);
    clock_t start, stop;
    start = clock();
    for(int i = 0; i < timeInputSize(iter); i++) {
        ht.insert(genRandomInt());
    }
    stop = clock();
    double* arr_time = is_quadratic ? quadratic_time_results : double_time_results;
    arr_time[iter] = ((double)(stop - start))/((double)CLOCKS_PER_SEC);

    int found = 0;
    for(int i = 0; i < findInputSize(iter); i++) {
        if(ht.contains(genRandomInt())) found++;
    }
    int* arr_find = is_quadratic ? quadratic_find_results : double_find_results;
    arr_find[iter] = found;

    arr_time = nullptr;
    arr_find = nullptr;
}

void Tester::runTests() {
    // genNewSeed();
    for(int i = 0; i < 5; i++) {
        for(int b = 0; b < 2; b++) {
            runTest(i, (bool)b);
        }
    }
}

void Tester::printTable(bool is_quadratic) {
    double* arr_time = is_quadratic ? quadratic_time_results : double_time_results;
    int* arr_find = is_quadratic ? quadratic_find_results : double_find_results;

    std::cout << std::setw(6 * CELL_W + 10) << std::setfill('_') << '_';
    std::cout << "\n|";
    printCell<std::string>("Input Size:", CELL_W + 2);
    std::cout << '|';
    for(int i = 0; i < 5; i++) {
        printCell<int>(timeInputSize(i), CELL_W);
        std::cout << '|'; 
    }

    std::cout << '\n';
    std::cout << std::setw(6 * CELL_W + 10) << std::setfill('_') << '_';
    std::cout << "\n|";
    printCell<std::string>("Build Time (s):", CELL_W + 2);
    std::cout << '|';
    for(int i = 0; i < 5; i++) {
        printCellFloat(arr_time[i], CELL_W);
        std::cout << '|';
    }

    std::cout << '\n';
    std::cout << std::setw(6 * CELL_W + 10) << std::setfill('_') << '_';
    std::cout << "\n|";
    printCell<std::string>("Items Found:", CELL_W + 2);
    std::cout << '|';
    for(int i = 0; i < 5; i++) {
        printCell<int>(arr_find[i], CELL_W);
        std::cout << '|';
    }

    std::cout << '\n';
    std::cout << std::setw(6 * CELL_W + 10) << std::setfill('_') << '_';
    std::cout << "\n|";
    printCell<std::string>("Items Not Found:", CELL_W + 2);
    std::cout << '|';
    for(int i = 0; i < 5; i++) {
        printCell<int>(findInputSize(i) - arr_find[i], CELL_W);
        std::cout << '|';
    }
    std::cout << '\n';

    arr_time = nullptr;
    arr_find = nullptr;
}

void Tester::printResults() {
    std::cout << std::left << std::setw(6 * CELL_W + 10) << std::setfill('~') << "Performance - Quadratic Probing";
    std::cout << "\n\n";
    printTable(true); // print quadratic probing results
    std::cout << "\n\n";

    std::cout << std::left << std::setw(6 * CELL_W + 10) << std::setfill('~') << "Performance - Double Hashing";
    std::cout << "\n\n";
    printTable(false); // print double hashing results
    std::cout << "\n\n";
}

void Tester::run() {
    runTests();
    printResults();
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