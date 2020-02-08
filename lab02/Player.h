#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>

struct Player {
    std::string name;
    int goalcount;
};

std::ostream& operator<<(std::ostream& o, const Player& p);

bool operator==(const Player& p1, const Player& p2);

#endif