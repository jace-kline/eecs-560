#include "GraphHandler.h"

GraphHandler::GraphHandler() {
    islands = nullptr;
}

GraphHandler::~GraphHandler() {
    if(islands != nullptr) {
        delete[] islands;
        islands = nullptr;
    }
}

void GraphHandler::loadFromFile(std::string filename) {
    std::string ln;
    std::ifstream fs;
    int n = 0;

    // open file and count the number of lines until the "n, <...>" line
    fs.open(filename);
    if(!fs.is_open()) std::cout << "Could not open data file.\n";
    while(std::getline(fs, ln)) {
        if(ln.substr(0,2) == "n," || ln.substr(0,3) == "n ,") break;
        else n++;
    }
    fs.close();

    // Create the member vars dynamically
    islands = new Island[n];
    g.n = n;
    g.arr = new List<AdjEntry>[n];

    // Reopen the file
    fs.open(filename);

    // Read and store the islands
    for(int i = 0; i < n; i++) {
        if(std::getline(fs, ln)) islands[i] = parseIsland(ln);
    }

    // Trash the line with "n,<#islands>"
    std::getline(fs, ln);

    // Read and store values into the adjacency matrix
    int w;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            fs >> w;
            if(j > i && w > 1) g.add(i, j, w);
        }
    }
    fs.close();
}

Island parseIsland(std::string line) {
    std::string name;
    int id;
    int comma_index = -1;
    for(unsigned int i = 0; i < line.size(); i++) {
        if(line.at(i) == ',') {
            comma_index = i;
            break;
        }
    }
    if(comma_index != -1) {
        name = line.substr(0,comma_index);
        id = std::stoi(line.substr(comma_index + 1, line.size() - comma_index - 1));
    }
    return Island { id, name };
}

void GraphHandler::search(bool mode) {
    SearchReturn sr = SearchReturn();
    if(mode) g.dfs(sr);
    else g.bfs(sr);

    std::cout << "Tree Edges: ";
    for(int i = 1; i <= sr.tree_edges.getLength(); i++) {
        WEdge e = sr.tree_edges.getEntry(i);
        std::cout << '(' << islands[e.i].name << ", " << islands[e.j].name << ") ";
    }

    std::cout << '\n' << (mode ? "Back" : "Cross") << " Edges: ";
    for(int i = 1; i <= sr.nontree_edges.getLength(); i++) {
        WEdge e = sr.nontree_edges.getEntry(i);
        std::cout << '(' << islands[e.i].name << ", " << islands[e.j].name << ") ";
    }
    std::cout << '\n';
}

void GraphHandler::bfs() {
    search(0);
}

void GraphHandler::dfs() {
    search(1);
}

void GraphHandler::mst(bool mode) {
    MSTReturn ret = MSTReturn();
    if(mode) g.primMST(ret);
    else g.kruskalMST(ret);
    if(!ret.solution) {
        std::cout << "No MST could be constructed for the given graph.\n";
    } else {
        int len = 0;
        for(int i = 1; i <= ret.edges.getLength(); i++) {
            WEdge e = ret.edges.getEntry(i);
            len += e.weight;
            std::cout << '(' << islands[e.i].name << ", " << islands[e.j].name << "){" << e.weight << "} ";
        }
        std::cout << "\nTotal length of the route = " << len << " miles.\n";
        std::cout << "Estimated construction cost = " << len << "*250K = " << (len * 250) << "K $\n";
    }
}

void GraphHandler::kruskalMST() {
    mst(0);
}

void GraphHandler::primMST() {
    mst(1);
}