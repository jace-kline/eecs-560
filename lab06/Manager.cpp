#include "Manager.h"

Manager::Manager() {}
Manager::~Manager() {}

void Manager::constructFromFile() {
    std::ifstream fs;
    int x;
    fs.open("data.txt");
    while(fs >> x) {
        tree.add(x);
    }
    fs.close();
}

void Manager::addItem(int x) {
    std::cout << "Element " << x << " was " << (tree.add(x) ? "" : "not") << " successfully added.\n";
}

void Manager::deleteItem(int x) {
    std::cout << "Element " << x << " was " << (tree.remove(x) ? "" : "not") << " successfully removed.\n";
}

void Manager::inorderSuccessor(int x) {
    try {
        int y = tree.inorderSuccessor(x);
        std::cout << "The inorder successor of " << x << " is " << y << '\n';
    } catch(std::runtime_error& e) {
        std::cout << "The element " << x << " was not found or it is the highest-priority element in the tree.\n";
    }
}

void Manager::printLevelOrder() {
    tree.traverseLevel(printFunc);
}

void Manager::printSpiralLevelOrder() {
    tree.traverseSpiralLevel(printFunc);
}

void Manager::printLeftSideView() {
    tree.traverseLeftSide(printFunc);
}

void Manager::printRightSideView() {
    tree.traverseRightSide(printFunc);
}

void Manager::kthSmallestItem(int k) {
    try{
        int y = tree.kthUniqueItem(k);
        std::cout << "The kth smallest (unique) item is " << y << '\n';
    } catch(std::runtime_error& e) {
        std::cout << "The integer k provided was too small or too large. No element found.\n";
    }
}

void printFunc(const int& x) {
    std::cout << x << ", ";
}