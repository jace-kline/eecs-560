#include "GraphHandler.h"

GraphHandler::GraphHandler() : islands(nullptr), g(0, nullptr) {}

GraphHandler::~GraphHandler() {
    if(islands != nullptr) {
        delete[] islands;
        islands = nullptr;
    }
}

// void GraphHandler::clear() {
//     if(islands != nullptr) {
//         delete[] islands;
//         islands = nullptr;
//     }
//     // if(g.a != nullptr) {
//     //     for(int i = 0; i < g.n; i++) {
//     //         delete[] g.a[i];
//     //         g.a[i] = nullptr;
//     //     }
//     //     delete[] g.a;
//     //     g.a = nullptr;
//     // }
//     // g.n = 0;
// }

void GraphHandler::loadFromFile(std::string filename) {
    std::string ln;
    std::ifstream fs;

    // open file and count the number of lines until the "n, <...>" line
    fs.open(filename);
    if(!fs.is_open()) std::cout << "Could not open data file.\n";
    while(std::getline(fs, ln)) {
        if(ln.substr(0,2) == "n," || ln.substr(0,3) == "n ,") break;
        else g.n++;
    }
    fs.close();

    // Create the member arrays dynamically
    islands = new Island[g.n];

    g.a = new int*[g.n];
    for(int i = 0; i < g.n; i++) {
        g.a[i] = new int[g.n];
        for(int j = 0; j < g.n; j++) g.a[i][j] = -1;
    }

    // Reopen the file
    fs.open(filename);

    // Read and store the islands
    for(int i = 0; i < g.n; i++) {
        if(std::getline(fs, ln)) islands[i] = parseIsland(ln);
    }

    // Trash the line with "n,<#islands>"
    std::getline(fs, ln);

    // Read and store values into the weight matrix
    int t;
    for(int i = 0; i < g.n; i++) {
        for(int j = 0; j < g.n; j++) {
            fs >> t;
            // std::cout << "a[" << i << "][" << j << "] = " << t << '\n';
            if(i == j) g.a[i][j] = 0;
            else g.a[i][j] = t;
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
    SearchReturn sr;
    if(mode) sr = g.dfs();
    else sr = g.bfs();

    std::cout << "Tree Edges: ";
    for(int i = 0; i < sr.tree_edges.size(); i++) {
        WEdge e = sr.tree_edges.at(i);
        std::cout << '(' << islands[e.i].name << ", " << islands[e.j].name << ") ";
    }

    std::cout << '\n' << (mode ? "Back" : "Cross") << " Edges: ";
    for(int i = 0; i < sr.nontree_edges.size(); i++) {
        WEdge e = sr.nontree_edges.at(i);
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
    std::vector<WEdge> edges = mode ? g.primMST() : g.kruskalMST();
    if(edges.empty()) {
        std::cout << "No MST could be constructed for the given graph.\n";
    } else {
        int len = 0;
        for(int i = 0; i < edges.size(); i++) {
            WEdge e = edges.at(i);
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