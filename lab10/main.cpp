#include "IO.h"
#include "DSHandler.h"
#include <fstream>

void displayMainMenu();

int main() {
    DSHandler dshandler;

    // Menu loop
    int input = 0;
    while(input != 6) {
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
            case 6: std::cout << "Exiting program.\n"; break;
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
              << "6. Exit\n\n";
}
