#include <iostream>
#include <fstream>
#include <string>
#include "List.h"
#include "Node.h"

bool generateListFromFile(List<int>&, std::string);
void runInteractive(List<int>&);
bool isGoodInput();
void displayMenu();
int promptResponse();
void performAction(List<int>&, int);
int promptIntegerInput(std::string);
void printList(List<int>& l);
void printNodeChain(Node<int>* n);



int main(int argc, char** argv) {
    List<int> l = List<int>();
    if(!generateListFromFile(l, (argc > 1 ? argv[1] : "data.txt"))) {
        std::cout << "Error reading input data from file. Exiting.\n";
        return 1;
    }
    runInteractive(l);
    return 0;
}

bool generateListFromFile(List<int>& l, std::string filename) {
    std::ifstream fs;
    fs.open(filename);
    if(!fs) return false;
    int x;
    while(fs >> x) {
        l.insertFront(x);
    }
    fs.close();
    return true;
}

void runInteractive(List<int>& l) {
    int inputOption = 0;
    do {
        displayMenu();
        inputOption = promptResponse();
        performAction(l, isGoodInput() ? inputOption : 0);
    }while(inputOption != 11);
}

bool isGoodInput() {
    if(std::cin.fail()) {
        std::cout.clear();
        std::cin.ignore();
        return false;
    }
    return true;
}

void displayMenu() {
    std::cout << "\n\n1. Is Empty\n"
              << "2. Length\n"
              << "3. Insert\n"
              << "4. Delete\n"
              << "5. Delete Duplicates\n"
              << "6. Find\n"
              << "7. Find Next\n"
              << "8. Print\n"
              << "9. Reverse List\n"
              << "10. Print At\n"
              << "11. Exit\n\n";
}

int promptResponse() {
    int input = 0;
    std::cout << "> ";
    std::cin >> input;
    return input;
}

void performAction(List<int>& l, int opt) {
    switch(opt) {
        case 1: {
            if(l.isEmpty()) std::cout << "The List is Empty\n";
            else std::cout << "The list is not empty";
            break;
        }
        case 2: {
            std::cout << "The length of the list is: " << l.getLength() << '\n';
            break;
        }
        case 3: {
            int x = promptIntegerInput("Choose an integer to be inserted:\n> ");
            l.insertFront(x);
            break;
        }
        case 4: {
            int x = promptIntegerInput("Choose an integer to be deleted from the list:\n> ");
            if(l.removeObj(x)) std::cout << "The last occurrence of " << x << " has been removed from the list.\n";
            else std::cout << "The integer " << x << " was not removed from the list because it was not in the list.\n";
            break;
        }
        case 5: {
            l.removeDuplicates();
            std::cout << "Duplicates have been deleted from the list.\n";
            break;
        }
        case 6: {
            int x = promptIntegerInput("Choose an integer to determine whether it is in the list.\n> ");
            if(l.contains(x)) std::cout << "The integer " << x << " is in the list.\n";
            else std::cout << "The integer " << x << " is not in the list.\n";
            break;
        }
        case 7: {
            int x = promptIntegerInput("Choose an integer to find the integer that follows it:\n> ");
            Node<int>* n = l.nodeFromItem(x);
            if(n == nullptr) std::cout << "The integer " << x << " is not in the list. Hence, there is no next element.\n";
            else {
                if(n->getNext() == nullptr) std::cout << "The integer " << x << " is the last element in the list. Hence, there is no next element.\n";
                else std::cout << "The integer " << n->getNext()->getItem() << " is the integer that follows " << x << " in the list.\n";
            }
            break;
        }
        case 8: {
            printList(l);
            break;
        }
        case 9: {
            List<int> lReverse = l;
            lReverse.reverse();
            std::cout << "Reversed ";
            printList(lReverse);
            break;
        }
        case 10: {
            int x = promptIntegerInput("Input an integer index to print the value located there.\n> ");
            try {
                int y = l.getEntry(x);
                std::cout << "The element at position " << x << " is: " << y << '\n';
            }
            catch (std::runtime_error& e) {
                std::cout << e.what();
            }
            break;
        }
        case 11: {
            break;
        }
        default: {
            std::cout << "Invalid choice. Input an integer from 1 to 11.\n";
        }
    }
}

int promptIntegerInput(std::string msg) {
    int x;
    while(true) {
        std::cout << msg;
        std::cin >> x;
        if(isGoodInput()) return x;
        else std::cout << "Invalid input. Please try again. You must input a valid integer\n";
    }
}

void printList(List<int>& l) {
    if(l.isEmpty()) std::cout << "The list is empty.\n";
    else {
        std::cout << "List: ";
        printNodeChain(l.head());
    }
}

void printNodeChain(Node<int>* n) {
    std::cout << n->getItem() << " ";
    if(!(n->isLeaf())) printNodeChain(n->getNext());
    else std::cout << '\n';
}
