#include "IO.h"

int promptBoundedInt(std::string msg, int low = INT32_MIN, int high = INT32_MAX);

std::ostream& operator<<(std::ostream& os, const Record& r) {
    os << r.first_name << ',' << r.last_name << ',' << r.priority;
    return os;
}

int promptResponse() {
    return promptBoundedInt("> ", 1);
}

bool isGoodInput() {
    if(std::cin.fail()) {
        std::cout.clear();
        std::cin.ignore();
        return false;
    }
    return true;
}

template <typename I>
I promptInput(std::string msg) {
    I x;
    while(true) {
        std::cout << msg;
        std::cin >> x;
        if(isGoodInput()) return x;
        else std::cout << "Invalid input. Please try again.\n";
    }
}

Record promptRecord(RecordType t, KeyOption o) {
    std::string fname = promptInput<std::string>(
        "Enter " + std::string(t == PATIENT ? "patient's" : "doctor's") + " first name:\n> "
    );
    std::string lname = promptInput<std::string>(
        "Enter " + std::string(t == PATIENT ? "patient's" : "doctor's") + " last name:\n> "
    );
    int priority = (
        o == KEY ? promptBoundedInt("Enter " + std::string(t == PATIENT ? "patient's urgency:\n> " : "doctor's patient count:\n> "), 0) : 0
    );
    return (Record {fname, lname, priority});
}

int promptBoundedInt(std::string msg, int low, int high) {
    int input = -1;
    while(true) {
        input = promptInput<int>(msg);
        if(input < low) std::cout << "Input value too low. Please try again.\n";
        else if(input > high) std::cout << "Input value too high. Please try again.\n";
        else break;
    }
    return input;
}