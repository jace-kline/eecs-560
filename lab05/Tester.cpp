#include "Tester.h"

Tester::Tester() {}
Tester::~Tester() {}

void Tester::genNewSeed() const {
    srand(time(NULL));
}

int Tester::timeInputSize(int iter) const {
    return(M * floor((float)(iter + 1) / 10));
}

int Tester::findInputSize(int iter) const {
    return(M * floor((float)(iter + 1) / 100));
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
    
    time_t start, stop;
    time(&start);
    for(int i = 0; i < timeInputSize(iter); i++) {
        ht.insert(genRandomInt());
    }
    time(&stop);
    if(is_quadratic) quadratic_time_results[iter] = difftime(stop, start);
    else double_time_results[iter] = difftime(stop, start);

    int found = 0;
    time(&start);
    for(int i = 0; i < findInputSize(iter); i++) {
        if(ht.contains(genRandomInt())) found++;
    }
    time(&stop);


}