#include "Record.h"

Record Record::operator=(const Record& r) {
    first_name = r.first_name;
    last_name = r.last_name;
    priority = r.priority;
}

bool operator==(const Record& r1, const Record& r2) {
    return(r1.first_name == r2.first_name && r1.last_name == r2.last_name);
}

bool operator<=(const Record& r1, const Record& r2) {
    return(r1.priority <= r2.priority);
}

bool operator>=(const Record& r1, const Record& r2) {
    return(r1.priority >= r2.priority);
}

bool operator<(const Record& r1, const Record& r2) {
    return(r1.priority < r2.priority);
}

bool operator>(const Record& r1, const Record& r2) {
    return(r1.priority > r2.priority);
}