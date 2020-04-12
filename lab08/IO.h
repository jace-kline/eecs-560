#include <iostream>
#include <sstream>
#include "Game.h"

std::ostream& operator<<(std::ostream& os, const Game& g);

int promptResponse();
bool isGoodInput();

template <typename I>
I promptInput(std::string msg);

int promptBoundedInt(std::string msg, int low, int high);

Game promptGameInput();