#include "AdjEntry.h"

bool operator==(const AdjEntry& ae1, const AdjEntry& ae2) {
    return(ae1.vertex == ae2.vertex && ae1.weight == ae2.weight);
}

// bool AdjEntry::operator==(const AdjEntry& other) {
//     return(vertex == other.vertex && weight == other.weight);
// }