#ifndef WGRAPH_H
#define WGRAPH_H

#include "WEdge.h"
#include "AdjEntry.h"
#include "../List/List.h"
#include "../Heap/Heap.h"
#include "../DisjointSet/DSetCollection.h"

struct SearchReturn {
    List<WEdge> tree_edges;
    List<WEdge> nontree_edges;
};

struct MSTReturn {
    bool solution;
    List<WEdge> edges;
};

struct AdjList {
    int n;
    List<AdjEntry>* arr;
    
    AdjList();
    AdjList(int size);
    ~AdjList();

    bool add(int i, int j, int w);
    bool validVertex(int i);
    int cost(int i, int j);
    WEdge edge(int i, int j);

    // returns heap of all edges, ordered (min) on weight
    void edgesHeap(Heap<WEdge>& h);

    // creates DSetCollection (disjoint sets) of all vertices
    void vertexDSets(DSetCollection<int>& dsets);

    void kruskalMST(MSTReturn& ret);

    void primMST(MSTReturn& ret);

    void dfs(SearchReturn& ret);
    void dfs_help(int i, bool visited[], SearchReturn& ret);

    void bfs(SearchReturn& ret);

};


#endif