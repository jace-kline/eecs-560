#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>

struct Player {
    std::string name;
    int goalcount;
};

std::ostream& operator<<(std::ostream& o, const Player& p) {
    o << p.name << " " << p.goalcount;
    return o;
}

#endif