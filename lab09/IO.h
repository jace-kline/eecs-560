#include <iostream>
#include <sstream>

int promptResponse();
bool isGoodInput();

template <typename I>
I promptInput(std::string msg);

int promptBoundedInt(std::string msg, int low, int high);