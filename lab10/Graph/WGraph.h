#ifndef WGRAPH_H
#define WGRAPH_H

#include "WEdge.h"
#include "../DisjointSet/DSetCollection.h"
#include "../Heap/Heap.h"
// #include "../Queue/Queue.h"
#include <vector>

struct SearchReturn {
    std::vector<WEdge> tree_edges;
    std::vector<WEdge> nontree_edges;

    SearchReturn();
    SearchReturn(const SearchReturn& other);
    SearchReturn& operator=(const SearchReturn& other);
};

// The vertices are all labeled {0 .. n-1}
// If a[i][j] = -1 -> no adjacency connection
// If i = j -> a[i][j] = 0
// Otherwise, a[i][j] = weight of edge from i to j
struct WGraph {
    int n;
    int **a;
    
    // WGraph();
    WGraph(int, int **);
    ~WGraph();

    bool validVertex(int i);
    int cost(int i, int j);

    // returns adjacency list for a given vertex
    // std::vector<int> adjList(int i);

    // returns heap of edges, ordered (min) on weight
    Heap<WEdge> edgesHeap();

    // returns DSetCollection (disjoint sets) of all vertices
    DSetCollection<int> vertexDSets();

    // // returns DSetCollection (disjoint sets) of all edges
    // DSetCollection<WEdge>* edgeDSets();

    // returns a queue of the edges for kruskal's method
    // in the order they were added
    // Returns nullptr if can't construct MST
    std::vector<WEdge> kruskalMST();

    std::vector<WEdge> primMST();
    void enqueueViableEdges(int i, Heap<WEdge>& edges_q, std::vector<int>& visited_vertices);

    // Returns a disjoint set collection of the edges in the graph
    // The tree edges are those in the same set as 0
    // The back edges are those not in the same set as 0
    SearchReturn dfs();
    void dfs_help(int i, bool* visited, SearchReturn& sr);

    SearchReturn bfs();

};

template <typename T>
bool inVector(const T& x, std::vector<T> vect);


#endif