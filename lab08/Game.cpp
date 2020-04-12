#include "Game.h"

Game Game::operator=(const Game& g) {
    name = g.name;
    downloads = g.downloads;
    return(*this);
}

bool operator==(const Game& g1, const Game& g2) {
    return(g1.name == g2.name && g1.downloads == g2.downloads);
}

bool operator<=(const Game& g1, const Game& g2) {
    return(g1.downloads <= g2.downloads);
}

bool operator>=(const Game& g1, const Game& g2) {
    return(g1.downloads >= g2.downloads);
}

bool operator<(const Game& g1, const Game& g2) {
    return(g1.downloads < g2.downloads);
}

bool operator>(const Game& g1, const Game& g2) {
    return(g1.downloads > g2.downloads);
}
