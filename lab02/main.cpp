
#define BUCKETS 7

#include <fstream>
#include <iostream>
#include <string>
#include "./Player.h"
#include "./HashTable.h"

int compareVal = 0;
int hits = 0;
Player contextPlayer;

int hash(const int& key, int size);
int playerToKey(const Player& p);
bool genHashTableFromFile(HashTable<Player,int>& ht, std::string filename);
void runInteractive(HashTable<Player,int>& ht);
bool isGoodInput();
void displayMenu();
int promptResponse();
void performAction(HashTable<Player,int>& ht, int code);

template <typename I>
I promptInput(std::string msg);
Player promptPlayerInput();
bool namesClashFoldFunc(const Player& cur, bool accum);
void printPlayer(const Player& p);
void printName(const Player& p);
void printWhenGoalCountEqual(const Player& p);
void printWhenGoalCountGreater(const Player& p);
void printWhenGoalCountLess(const Player& p);

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
              << "4. Players with goal count equal to a given number\n"
              << "5. Players with goal count greater than a given number\n"
              << "6. Players with goal count less than a given number\n"
              << "7. Exit\n\n";
}

void performAction(HashTable<Player,int>& ht, int code) {
    switch (code)
    {
    case 1: {
        std::cout << "Insert a player into the table...\n";
        contextPlayer = promptPlayerInput();
        if(!ht.fold<bool>(namesClashFoldFunc, false)) {
            if(ht.insert(contextPlayer)) std::cout << "Player record successfully inserted.\n";
        }
        else std::cout << "Player record could not be added. Insertion record is a duplicate name.\n";
        break;
    }
    case 2: {
        std::cout << "Remove a player from the table...\n";
        Player p = promptPlayerInput();
        if(ht.remove(p)) std::cout << "The player, " << p << ", was successfully removed.\n";
        else std::cout << "No specified player record exists. No removal occurred.\n";
        break;
    }
    case 3: {
        ht.printTable(printPlayer);
        break;
    }
    case 4: {
        compareVal = promptInput<int>("Enter a goal count:\n> ");
        hits = 0;
        std::cout << "Players with goal count equal to " << compareVal << ": ";
        ht.traverseObjects(printWhenGoalCountEqual);
        std::cout << (hits == 0 ? "No Players Match\n" : "\n");
        std::cout << '\n';
        break;
    }
    case 5: {
        compareVal = promptInput<int>("Enter a goal count:\n> ");
        hits = 0;
        std::cout << "Players with goal count greater than " << compareVal << ": ";
        ht.traverseObjects(printWhenGoalCountGreater);
        std::cout << (hits == 0 ? "No Players Match\n" : "\n");
        break;
    }
    case 6: {
        compareVal = promptInput<int>("Enter a goal count:\n> ");
        hits = 0;
        std::cout << "Players with goal count less than " << compareVal << ": ";
        ht.traverseObjects(printWhenGoalCountLess);
        std::cout << (hits == 0 ? "No Players Match\n" : "\n");
        break;
    }
    case 7: {
        std::cout << "Ending program.\n";
        break;
    }
    default:
        std::cout << "Invalid choice. Input an integer from 1 to 7.\n";
        break;
    }
}

int promptResponse() {
    int input = 0;
    std::cout << "> ";
    std::cin >> input;
    return input;
}

template <typename I>
I promptInput(std::string msg) {
    I x;
    while(true) {
        std::cout << msg;
        std::cin >> x;
        if(isGoodInput()) return x;
        else std::cout << "Invalid input. Please try again.\n";
    }
}

Player promptPlayerInput() {
    std::string name;
    int goalcount = -1;
    name = promptInput<std::string>("Input a player name:\n> ");
    while(true) {
        goalcount = promptInput<int>("Input the goal count for this player:\n> ");
        if(goalcount < 0) std::cout << "The goal count provided was invalid. Please try again.\n";
        else break;
    }
    return(Player {name, goalcount});
}

bool namesClashFoldFunc(const Player& cur, bool accum) {
    return(contextPlayer.name == cur.name || accum);
}

void printWhenGoalCountEqual(const Player& p) {
    if(p.goalcount == compareVal){
        hits++;
        std::cout << p.name << ", ";
    }
}

void printWhenGoalCountGreater(const Player& p) {
    if(p.goalcount > compareVal) {
        hits++;
        std::cout << p.name << ", ";
    }
}

void printWhenGoalCountLess(const Player& p) {
    if(p.goalcount < compareVal) {
        hits++;
        std::cout << p.name << ", ";
    }
}

void printName(const Player& p) {
    std::cout << p.name;
}

void printPlayer(const Player& p) {
    std::cout << p;
}
