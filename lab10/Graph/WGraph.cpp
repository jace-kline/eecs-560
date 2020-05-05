#include "WGraph.h"

SearchReturn::SearchReturn() {
    tree_edges = std::vector<WEdge>();
    nontree_edges = std::vector<WEdge>();
}

SearchReturn::SearchReturn(const SearchReturn& other) {
    tree_edges = other.tree_edges;
    nontree_edges = other.nontree_edges;
}

SearchReturn& SearchReturn::operator=(const SearchReturn& other) {
    tree_edges = other.tree_edges;
    nontree_edges = other.nontree_edges;
    return *this;
}

// WGraph::WGraph() {
//     n = 0;
//     a = nullptr;
// }

WGraph::WGraph(int size, int **arr) {
    n = size;
    a = arr;
}

WGraph::~WGraph() {
    if(a != nullptr) {
        for(int i = 0; i < n; i++) {
            delete[] a[i];
            a[i] = nullptr;
        }
        delete[] a;
        a = nullptr;
    }
}

bool WGraph::validVertex(int i) {
    return (i >= 0 && i < n);
}

int WGraph::cost(int i, int j) {
    if(validVertex(i) && validVertex(j)) {
        return a[i][j];
    }
    return -1;
}

// std::vector<int> WGraph::adjList(int j) {
//     std::vector<int> l;
//     for(int i = 0; i < n; i++) {
//         if(a[j][i] > 0) l.push_back(a[j][i]);
//     }
//     return l;
// }

Heap<WEdge> WGraph::edgesHeap() {
    Heap<WEdge> h = Heap<WEdge>(MIN, 2, (n * (n - 1)) / 2);
    WEdge e;
    for(int i = 0; i < n; i++) {
        for(int j = i+1; j < n; j++) {
            if(cost(i,j) > 0) {
                e = WEdge(i, j, a[i][j]);
                h.insert(e);
            }
        }
    }
    return h;
}

DSetCollection<int> WGraph::vertexDSets() {
    DSetCollection<int> dsets = DSetCollection<int>(n, AUTO);
    for(int i = 0; i < n; i++) {
        dsets.initSingleton(i);
    }
    return dsets;
}

// DSetCollection<WEdge>* WGraph::edgeDSets() {
//     DSetCollection<WEdge>* dsets = new DSetCollection<WEdge>((n * (n - 1)) / 2, AUTO);
//     WEdge e;
//     for(int i = 0; i < n; i++) {
//         for(int j = i+1; j < n; j++) {
//             e = WEdge(i, j, a[i][j]);
//             dsets->initSingleton(e);
//         }
//     }
//     return dsets;
// }

std::vector<WEdge> WGraph::kruskalMST() {
    std::vector<WEdge> solution_edges;
    Heap<WEdge> edge_candidates = edgesHeap();
    DSetCollection<int> vertex_dsets = vertexDSets();

    while(!edge_candidates.isEmpty() && (solution_edges.size() < n - 1)) {
        WEdge e = edge_candidates.popFront();
        if(vertex_dsets.findRepr(e.i) != vertex_dsets.findRepr(e.j)) {
            solution_edges.push_back(e);
            vertex_dsets.mkUnion(e.i,e.j);
        }
    }

    if(solution_edges.size() == n - 1) return solution_edges;
    else {
        solution_edges.clear();
        return solution_edges;
    }
}

std::vector<WEdge> WGraph::primMST() {
    std::vector<WEdge> solution_edges;
    Heap<WEdge> edge_candidates = Heap<WEdge>(MIN, 2, (n * (n - 1)) / 2);
    DSetCollection<int> vertex_dsets = vertexDSets();
    std::vector<int> visited_vertices;

    // enqueue all edges of vertex 0 (initial)
    enqueueViableEdges(0, edge_candidates, visited_vertices);
    while(!edge_candidates.isEmpty() && (solution_edges.size() < n - 1)) {
        WEdge e = edge_candidates.popFront();
        int k = inVector(e.i, visited_vertices) ? e.j : e.i;
        visited_vertices.push_back(k);
        enqueueViableEdges(k, edge_candidates, visited_vertices);
    }

    if(solution_edges.size() == n - 1) return solution_edges;
    else {
        // returns empty vector on failure to generate MST
        solution_edges.clear();
        return solution_edges;
    }   
}

void WGraph::enqueueViableEdges(int i, Heap<WEdge>& edges_heap, std::vector<int>& visited_vertices) {
    for(int k = 0; k < n; k++) {
        int j = a[i][k];
        if(j > 0) {
            if(!inVector(j, visited_vertices)) {
                WEdge e = WEdge(i, j, a[i][j]);
                edges_heap.insert(e);
            }
        }
    }
}

SearchReturn WGraph::dfs() {
    bool visited[n] = { 0 };
    SearchReturn sr;
    dfs_help(0, visited, sr);
    return sr;
}

void WGraph::dfs_help(int i, bool* visited, SearchReturn& sr) {
    visited[i] = true;
    for(int k = 0; k < n; k++) {
        int j = a[i][k];
        if(j > 0) {
            WEdge e = WEdge(i, j, a[i][j]);
            if(!visited[j]) {
                sr.tree_edges.push_back(e);
                dfs_help(j, visited, sr);
            } else {
                sr.nontree_edges.push_back(e);
            }
        }
    }
}

SearchReturn WGraph::bfs() {
    SearchReturn sr;
    bool visited[n];
    for(int i = 0; i < n; i++) {
        visited[i] = false;
    }
    std::vector<int> vert_queue;
    vert_queue.push_back(0);
    visited[0] = true;

    while(!vert_queue.empty()) {
        int i = vert_queue.back();
        vert_queue.pop_back();
        for(int k = 0; k < n; k++) {
            int j = a[i][k];
            if(j > 0) {
                WEdge e = WEdge(i, j, a[i][j]);
                if(!visited[j]) {
                    vert_queue.push_back(j);
                    visited[j] = true;
                    sr.tree_edges.push_back(e);
                } else {
                    sr.nontree_edges.push_back(e);
                }
            }
        }
    }
    return sr;
}

template <typename T>
bool inVector(const T& x, std::vector<T> vect) {
    for(int i = 0; i < vect.size(); i++) {
        if(vect.at(i) == x) return true;
    }
    return false;
}

