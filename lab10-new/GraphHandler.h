#ifndef GRAPH_HANDLER_H
#define GRAPH_HANDLER_H

#include <string>
#include <fstream>
#include <iostream>
#include "Graph/WGraph.h"

struct Island {
    int id;
    std::string name;
};

class GraphHandler
{
    private:
        Island *islands; // array of islands
        AdjList g;

    protected:
        // void clear();

        // mode = 0 -> bfs
        // mode = 1 -> dfs
        void search(bool mode);

        // mode = 0 -> kruskal
        // mode = 1 -> prim
        void mst(bool mode);
        
    public:
        GraphHandler();
        ~GraphHandler();

        // Load the graph data from the input file
        void loadFromFile(std::string filename);
        void bfs();
        void dfs();
        void kruskalMST();
        void primMST();
};

Island parseIsland(std::string line);

#endif