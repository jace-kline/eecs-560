#ifndef GAME_H
#define GAME_H

#include <string>

struct Game {
    std::string name;
    int downloads;

    Game operator=(const Game& g);
};

bool operator==(const Game& r1, const Game& r2);

// Compare priority values
bool operator<=(const Game& r1, const Game& r2);
bool operator>=(const Game& r1, const Game& r2);
bool operator<(const Game& r1, const Game& r2);
bool operator>(const Game& r1, const Game& r2);

#endif