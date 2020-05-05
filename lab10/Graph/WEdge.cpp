#include "WEdge.h"

WEdge::WEdge() : i(-1), j(-1), weight(-1) {}

WEdge::WEdge(int i1, int i2, int w) : i(i1), j(i2), weight(w) {}

bool operator<(const WEdge& e1, const WEdge& e2) {
    return(e1.weight < e2.weight);
}

bool operator>(const WEdge& e1, const WEdge& e2) {
    return(e1.weight > e2.weight);
}

bool operator<=(const WEdge& e1, const WEdge& e2) {
    return(e1.weight <= e2.weight);
}

bool operator>=(const WEdge& e1, const WEdge& e2) {
    return(e1.weight >= e2.weight);
}

bool operator==(const WEdge& e1, const WEdge& e2) {
    return(e1.weight == e2.weight && ((e1.i == e2.i && e1.j == e2.j) || (e1.i == e2.j && e1.j == e2.i)));
}