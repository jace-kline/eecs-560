#ifndef WEDGE_H
#define WEDGE_H

struct WEdge {
    int i;
    int j;
    int weight;

    WEdge();
    WEdge(int i1, int i2, int w);
};

bool operator>(const WEdge& e1, const WEdge& e2);
bool operator<(const WEdge& e1, const WEdge& e2);
bool operator>=(const WEdge& e1, const WEdge& e2);
bool operator<=(const WEdge& e1, const WEdge& e2);
bool operator==(const WEdge& e1, const WEdge& e2);

#endif