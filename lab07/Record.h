#ifndef DOCTOR_H
#define DOCTOR_H

#include <string>

typedef Record Doctor;
typedef Record Patient;

struct Record {
    std::string first_name;
    std::string last_name;
    int priority;

    Record operator=(const Record& r);
};

// Checks equality on the person's names
// Is this actually the same person?
bool operator==(const Record& r1, const Record& r2);

// Compare priority values
bool operator<=(const Record& r1, const Record& r2);
bool operator>=(const Record& r1, const Record& r2);
bool operator<(const Record& r1, const Record& r2);
bool operator>(const Record& r1, const Record& r2);



#endif