#include "./Player.h"

std::ostream& operator<<(std::ostream& o, const Player& p) {
    o << p.name << " " << p.goalcount;
    return o;
}

bool operator==(const Player& p1, const Player& p2) {
    return (p1.name == p2.name && p1.goalcount == p2.goalcount);
}