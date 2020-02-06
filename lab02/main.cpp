
#define BUCKETS 11

#include <fstream>
#include <iostream>
#include <string>
#include "./Player.h"
#include "./HashTable.h"

template class Node<Player>;
template class List<Player>;
template class HashTable<Player,int>;

int hash(const int& key, int size);
int playerToKey(const Player& p);
bool genHashTableFromFile(HashTable<Player,int>& ht, std::string filename);
void runInteractive(HashTable<Player,int>& ht);
bool isGoodInput();
void displayMenu();
int promptResponse();
void performAction(HashTable<Player,int>& ht, int code);
int promptIntegerInput(std::string msg);
Player promptPlayerInput();

int main(int argc, char** argv) {
    HashTable<Player,int> ht = HashTable<Player,int>(BUCKETS, playerToKey, hash);
    if(!genHashTableFromFile(ht, (argc > 1 ? argv[1] : "data.txt"))) {
        std::cout << "Error reading input data from file. Exiting.\n";
        return 1;
    }
    runInteractive(ht);
    return 0;
}

int hash(const int& key, int size) {
    return(key % size);
}

int playerToKey(const Player& p) {
    return(p.goalcount);
}

bool genHashTableFromFile(HashTable<Player,int>& ht, std::string filename) {
    std::ifstream fs;
    fs.open(filename);
    if(!fs) return false;

    std::string name;
    int goalcount;
    char comma;

    while(fs.peek() != EOF) {
        fs >> name;
        fs >> goalcount;
        fs >> comma;

        name.pop_back();
        ht.insert(Player {name, goalcount});
    }
    fs.close();
    return true;
}

void runInteractive(HashTable<Player,int>& ht) {
    int inputOption = 0;
    do {
        displayMenu();
        inputOption = promptResponse();
        performAction(ht, isGoodInput() ? inputOption : 0);
    }while(inputOption != 7);
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
    std::cout << "\n\n1. Add Player\n"
              << "2. Remove Player\n"
              << "3. Print Players Table\n"
              << "4. Players with goalcount equal to a given number\n"
              << "5. Players with goalcount greater than a given number\n"
              << "6. Players with goalcount less than a given number\n"
              << "7. Exit\n\n";
}

void performAction(HashTable<Player,int>& ht, int code) {
    switch (code)
    {
    case 1: {
        if(ht.insert(promptPlayerInput())) std::cout << "Player record successfully inserted.\n";
        else std::cout << "Player record could not be added. Something went wrong.\n";
        break;
    }
    case 2: {

        break;
    }
    case 3: {

        break;
    }
    case 4: {

        break;
    }
    case 5: {

        break;
    }
    case 6: {

        break;
    }
    case 7: {
        break;
    }
    default:
        std::cout << "Invalid choice. Input an integer from 1 to 7.\n";
        break;
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

Player promptPlayerInput() {
    std::string playerinfo;
    std::string name;
    int goalcount = -1;
    do {
        std::cout << "Input a player record in the form '<name>: <goalcount>':\n> ";
        std::cin >> playerinfo;

        int i = playerinfo.find(':');
        name = playerinfo.substr(0,i-1);
        goalcount = std::stoi(playerinfo.substr(i+2));

        if(goalcount < 0) std::cout << "The goal count provided was invalid. Please try again.\n";
        else break;
    }while(true);
    return(Player {name, goalcount});
}



