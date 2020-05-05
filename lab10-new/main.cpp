#include "IO.h"
#include "DSHandler.h"
#include "GraphHandler.h"
#include <fstream>

void displayMainMenu();

int main() {
    DSHandler dshandler;
    GraphHandler ghandler;
    ghandler.loadFromFile("data1.txt");

    // Menu loop
    int input = 0;
    while(input != 10) {
        displayMainMenu();
        input = promptResponse();
        switch (input)
        {
            case 1: {
                dshandler.loadFromFile("data.txt");
                break;
            }
            case 2: {
                dshandler.unionSets();
                break;
            }
            case 3: {
                dshandler.findRep();
                break;
            }
            case 4: {
                dshandler.pathCompress();
                break;
            }
            case 5: {
                dshandler.printPath();
                break;
            }
            case 6: {
                ghandler.bfs();
                break;
            }
            case 7: {
                ghandler.dfs();
                break;
            }
            case 8: {
                ghandler.kruskalMST();
                break;
            }
            case 9: {
                ghandler.primMST();
                break;
            }
            case 10: std::cout << "Exiting program.\n"; break;
            default:
                std::cout << "Invalid menu number. Please try again.\n";
                break;
        }
    }
}

void displayMainMenu() {
    std::cout << "\nChoose a command from the list:"
              << "\n\n1. Make Disjoint Sets\n"
              << "2. Union\n"
              << "3. Find\n"
              << "4. Path Compression\n"
              << "5. Print Path\n"
              << "6. BFS\n"
              << "7. DFS\n"
              << "8. Kruskal MST\n"
              << "9. Prim MST\n"
              << "10. Exit\n\n";
}
