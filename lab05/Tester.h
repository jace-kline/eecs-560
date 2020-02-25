#ifndef TESTER_H
#define TESTER_H

#include <stdlib.h>
#include <cmath>
#include <time.h>
#include "IntHash.h"
#include "HashTable.h"

#define MAX_GEN_VAL 5000000

struct FindResult {
    int found;
    int not_found;
};

class Tester {
    private:

        float quadratic_time_results[5];
        FindResult quadratic_find_results[5];

        float double_time_results[5];
        FindResult double_find_results[5];
        

    protected:
        void genNewSeed() const;
        int timeInputSize(int iter) const;
        int findInputSize(int iter) const;
        int genRandomInt() const;
        void runTest(int iter, bool is_quadratic);

    public:
        Tester();
        ~Tester();
};

#endif