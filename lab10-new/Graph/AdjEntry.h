#ifndef ADJ_ENTRY_H
#define ADJ_ENTRY_H

struct AdjEntry {
    int vertex;
    int weight;

    // bool operator==(const AdjEntry& other);
};

bool operator==(const AdjEntry& ae1, const AdjEntry& ae2);

#endif