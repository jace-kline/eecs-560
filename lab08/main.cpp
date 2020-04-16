#include "Maxmin.h"
#include "IO.h"
#include <fstream>

void displayMainMenu();

void fillHeap(Heap<Game>& h);

void printFunc(const Game& g);
int sumFunc(const Game& g, int accum);
void printDownloadFunc(const Game& g);

int main() {

    Heap<Game> h = Heap<Game>(2, 200);
    fillHeap(h);

    int input = 0;
    while(input != 8) {
        displayMainMenu();
        input = promptResponse();
        switch (input)
        {
            case 1: {
                Game g = promptGameInput();
                if(h.add(g)) {
                    std::cout << "Game '" << g.name << ',' << g.downloads << "' successfully added.\n";
                } else {
                    std::cout << "Error occurred while attempting to add the game.\n";
                }
                break;
            }
            case 2: {
                try {
                    Game g = h.peekMax();
                    if(h.deleteMax()) {
                        std::cout << "The game " << g.name << " with " << g.downloads << "K downloads has been deleted.\n";
                    } else std::cout << "Error occurred while attempting to delete max element.\n";
                } catch(std::runtime_error& e) {
                    std::cout << e.what() << '\n';
                }
                break;
            }
            case 3: {
                Game g = promptGameInput();
                if(h.deleteItem(g)) {
                    std::cout << "The game " << g.name << " with " << g.downloads << "K downloads has been deleted.\n";
                } else {
                    std::cout << "The given game was not found in the heap, and therefore was not deleted.\n";
                }
                break;
            }
            case 4: {
                h.traverseLevels(MIN, printFunc);
                std::cout << '\n';
                break;
            }
            case 5: {
                h.traverseLevels(MAX, printFunc);
                std::cout << '\n';
                break;
            }
            case 6: {
                std::cout << "Downloaded Games (Min Levels): " << h.foldLevels(MIN, sumFunc, 0) << '\n'; 
                break;
            }
            case 7: {
                std::cout << "Downloaded Games (Max Levels): " << h.foldLevels(MAX, sumFunc, 0) << '\n'; 
                break;
            }
            case 8: std::cout << "Exiting program.\n"; break;
            // case 9: h.traverseAll(printDownloadFunc); break;
            default:
                std::cout << "Invalid menu number. Please try again.\n";
                break;
        }
    }
}

void displayMainMenu() {
    std::cout << "\nChoose a command from the list:"
              << "\n\n1. Add Game\n"
              << "2. Delete Max Downloaded Game\n"
              << "3. Delete Game\n"
              << "4. Print Games at Min Levels\n"
              << "5. Print Games at Max Levels\n"
              << "6. Total Minimum Downloaded Games\n"
              << "7. Total Maximum Downloaded Games\n"
              << "8. Exit\n\n";
}

void fillHeap(Heap<Game>& h) {
    std::ifstream fs;
    std::string line;
    std::string name;
    int downloads;
    fs.open("data.txt");
    while(fs >> line) {
        for(unsigned int i = 0; i < line.size(); i++) {
            if(line.at(i) == ',') {
                name = line.substr(0, i);
                downloads = std::stoi(line.substr(i+1));
            }
        }
        h.add(Game {name, downloads});
    }
}

void printFunc(const Game& g) {
    std::cout << g.name << ", ";
}

int sumFunc(const Game& g, int accum) {
    return (accum + g.downloads);
}

void printDownloadFunc(const Game& g) {
    std::cout << g.name << ", ";
}