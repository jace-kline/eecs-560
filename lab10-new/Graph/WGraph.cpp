#include "WGraph.h"

AdjList::AdjList() {
    n = 0;
    arr = nullptr;
}

AdjList::AdjList(int size) {
    n = size;
    arr = new List<AdjEntry>[n];
}

AdjList::~AdjList() {
    if(arr != nullptr) delete[] arr;
}

bool AdjList::validVertex(int i) {
    return (i >= 0 && i < n);
}

bool AdjList::add(int i, int j, int w) {
    if(validVertex(i) && validVertex(j)) {
        arr[j].insertEnd(AdjEntry {i, w});
        arr[i].insertEnd(AdjEntry {j, w});
        return true;
    }
    return false;
}

WEdge AdjList::edge(int i, int j) {
    int w = cost(i,j);
    return WEdge { i, j, (w > 0 ? w : -1)};
}



int AdjList::cost(int i, int j) {
    if(validVertex(i) && validVertex(j)) {
        for(int k = 1; k <= arr[i].getLength(); k++) {
            if(arr[i].getEntry(k).vertex == j) return arr[i].getEntry(k).weight;
        }
    }
    return -1;
}

void AdjList::edgesHeap(Heap<WEdge>& h) {
    // Heap<WEdge> h = Heap<WEdge>(MIN, 2, (n * (n - 1)) / 2);
    for(int i = 0; i < n; i++) {
        for(int j = i+1; j < n; j++) {
            WEdge e = edge(i,j);
            if(e.weight > 0) {
                h.insert(e);
            }
        }
    }
}

void AdjList::vertexDSets(DSetCollection<int>& dsets) {
    // DSetCollection<int> dsets = DSetCollection<int>(n, AUTO);
    for(int i = 0; i < n; i++) {
        dsets.initSingleton(i);
    }
}

void AdjList::kruskalMST(MSTReturn& ret) {
    // std::vector<WEdge> solution_edges;
    Heap<WEdge> edge_candidates(MIN, 2, (n * (n-1)) / 2);
    edgesHeap(edge_candidates);
    DSetCollection<int> vertex_dsets(n, AUTO);
    vertexDSets(vertex_dsets);

    while(!edge_candidates.isEmpty() && (ret.edges.getLength() < n - 1)) {
        WEdge e = edge_candidates.popFront();
        if(vertex_dsets.findRepr(e.i) != vertex_dsets.findRepr(e.j)) {
            ret.edges.insertEnd(e);
            vertex_dsets.mkUnion(e.i,e.j);
        }
    }

    ret.solution = (ret.edges.getLength() == n - 1) ? true : false;
}

void AdjList::primMST(MSTReturn& ret) {
    // std::vector<WEdge> solution_edges;
    Heap<WEdge> edge_candidates(MIN, 2, (n * (n - 1)) / 2);
    DSetCollection<int> vertex_dsets(n, AUTO);
    vertexDSets(vertex_dsets);

    // enqueue all edges of vertex 0 (initial)
    for(int i = 0; i < n; i++) {
        WEdge e = edge(0,i);
        if(e.weight > 0) edge_candidates.insert(e);
    }

    while(!edge_candidates.isEmpty() && (ret.edges.getLength() < n - 1)) {
        // get candidate edge
        WEdge e = edge_candidates.popFront();
        
        // check to see if end vertex is already visited
        // if not, add the edge to the list
        if(vertex_dsets.findRepr(e.j) != vertex_dsets.findRepr(0)) {
            ret.edges.insertEnd(e);

            // add new candidate edges
            for(int i = 0; i < n; i++) {
                WEdge e_cand = edge(e.j, i);
                if(e_cand.weight > 0) edge_candidates.insert(e_cand);
            }
            vertex_dsets.mkUnion(e.j, 0);

        }
    }

    ret.solution = (ret.edges.getLength() == n - 1) ? true : false;
}

void AdjList::dfs(SearchReturn& ret) {
    bool visited[n] = { 0 };
    dfs_help(0, visited, ret);
}

void AdjList::dfs_help(int i, bool visited[], SearchReturn& ret) {
    visited[i] = true;
    for(int j = 0; j < n; j++) {
        WEdge e = edge(i, j);
        if(e.weight > 0) {
            if(!visited[j]) {
                ret.tree_edges.insertEnd(e);
                dfs_help(j, visited, ret);
            } else if(!(ret.tree_edges.contains(e) || ret.nontree_edges.contains(e))) {
                ret.nontree_edges.insertEnd(e);
            }
        }
    }
}

void AdjList::bfs(SearchReturn& ret) {
    bool visited[n] = { 0 };
    List<int> vert_queue;
    vert_queue.insertEnd(0);
    visited[0] = true;

    while(!vert_queue.isEmpty()) {
        int i = vert_queue.getEntry(1);
        vert_queue.removeAt(1);
        for(int j = 0; j < n; j++) {
            WEdge e = edge(i, j);
            if(e.weight > 0) {
                if(!visited[j]) {
                    vert_queue.insertEnd(j);
                    visited[j] = true;
                    ret.tree_edges.insertEnd(e);
                } else if(!(ret.tree_edges.contains(e) || ret.nontree_edges.contains(e))) {
                    ret.nontree_edges.insertEnd(e);
                }
            }
        }
    }
}

