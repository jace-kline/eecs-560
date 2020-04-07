#include "Record.h"
#include <iostream>
#include <sstream>

std::ostream& operator<<(std::ostream& os, const Record& r);

int promptResponse();
bool isGoodInput();

template <typename I>
I promptInput(std::string msg);

Record promptRecord(RecordType t, KeyOption o);

int promptBoundedInt(std::string msg, int low, int high);