#include "IO.h"
#include "Test.h"
#include <fstream>

void displayMainMenu();
void fillHeap(Heap& h);

int main() {
    // initialize random seed
    srand(time(NULL));

    // Build the heaps from "data.txt" file
    Heap h_leftist = Heap(LEFTIST);
    fillHeap(h_leftist);
    Heap h_skew = Heap(SKEW);
    fillHeap(h_skew);

    // Menu loop
    int input = 0;
    while(input != 6) {
        displayMainMenu();
        input = promptResponse();
        switch (input)
        {
            case 1: {
                std::cout << "Printing Leftist Heap in level-order:\n";
                h_leftist.printLevelOrder();
                break;
            }
            case 2: {
                try {
                    int x = h_leftist.popMin();
                    std::cout << "Deleted min element, " << x << ", from the heap.\n";
                    std::cout << "Printing Leftist Heap in level-order:\n";
                    h_leftist.printLevelOrder();
                } catch(std::runtime_error& e) {
                    std::cout << e.what() << '\n';
                }
                break;
            }
            case 3: {
                std::cout << "Printing Skew Heap in level-order:\n";
                h_skew.printLevelOrder();
                break;
            }
            case 4: {
                try {
                    int x = h_skew.popMin();
                    std::cout << "Deleted min element, " << x << ", from the heap.\n";
                    std::cout << "Printing Skew Heap in level-order:\n";
                    h_skew.printLevelOrder();
                } catch(std::runtime_error& e) {
                    std::cout << e.what() << '\n';
                }
                break;
            }
            case 5: {
                std::cout << "Running tests...\n\n";
                runTests();
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
              << "\n\n1. Test Build - Min Leftist Heap\n"
              << "2. Test Delete Min - Min Leftist Heap\n"
              << "3. Test Build - Min Skew Heap\n"
              << "4. Test Delete Min - Min Skew Heap\n"
              << "5. Test Performance of Heaps\n"
              << "6. Exit\n\n";
}

void fillHeap(Heap& h) {
    std::ifstream fs;
    int x;
    fs.open("data.txt");
    while(fs >> x) {
        h.insert(x);
    }
    fs.close();
}