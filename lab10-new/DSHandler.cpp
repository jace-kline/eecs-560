#include "DSHandler.h"

DSHandler::DSHandler() : dsets(100, MAN) {}

DSHandler::~DSHandler() {}

void DSHandler::loadFromFile(std::string filename) {
    std::ifstream fs;
    int x;

    fs.open(filename);
    if(!fs.is_open()) std::cout << "Could not open the given file.\n";

    while(fs >> x) {
        if(!dsets.initSingleton(x)) {
            std::cout << "Could not add element " << x << " because it is already in the set.\n";
        }
    }
    std::cout << "The disjoint sets have been constructed.\n";
    fs.close();
}

void DSHandler::unionSets() {
    std::cout << "Enter elements for the two sets you wish to union...\n";
    int x = promptInput<int>("First Element: ");
    int y = promptInput<int>("Second Element: ");
    try {
        int repX = dsets.findRepr(x);
        int repY = dsets.findRepr(y);
        int rep = dsets.mkUnion(x, y);
        std::cout << x << " (rep = " << repX << ") and " << y << " (rep = " << repY << ") have been merged.\n";
        std::cout << "The representative element is " << rep << '\n';
    } catch(const int& i) {
        std::cout << "Element " << i << " is not in the set. Union operation failed.\n";
    }
}

void DSHandler::findRep() {
    int x = promptInput<int>("Enter element to find:\n> ");
    try{
        int r = dsets.findRepr(x);
        std::cout << "Found element " << x << ". The representative element is " << r << ".\n";
    } catch(const int& y) {
        std::cout << "Could not find element " << x << ".\n";
    }
}

void DSHandler::pathCompress() {
    int x = promptInput<int>("Enter element on whose set you would like to perform path compression:\n> ");
    if(dsets.pathCompress(x)) {
        std::cout << "Path compression successful.\n";
    } else {
        std::cout << "Element " << x << " not found. Path compression failed.\n";
    }
}

void DSHandler::printPath() {
    int x = promptInput<int>("Enter element to its print path to the root:\n> ");
    if(!dsets.traversePath(x, printElement, printBridge)) {
        std::cout << "Element " << x << " is not in the set.\n";
    }
    std::cout << '\n';
}

void printElement(const int& x) {
    std::cout << x;
}

void printBridge() {
    std::cout << " -> ";
}
