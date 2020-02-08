
#define BUCKETS 7

#include <fstream>
#include <iostream>
#include <string>
#include "./Player.h"
#include "./HashTable.h"

// template class Node<Player>;
// template class List<Player>;
// template class HashTable<Player,int>;

static int compareVal = 0;
static Player contextPlayer;

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
bool namesClashFoldFunc(const Player& cur, bool accum);
void printNamesList(const List<Player>& l);
void printPlayer(const Player& p);
void printName(const Player& p);
bool isGoalCountEqual(const Player& p);
bool isGoalCountGreater(const Player& p);
bool isGoalCountLess(const Player& p);

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
        compareVal = promptIntegerInput("Enter a goal count:\n> ");
        printNamesList(ht.filter(isGoalCountEqual));
        break;
    }
    case 5: {
        compareVal = promptIntegerInput("Enter a goal count:\n> ");
        printNamesList(ht.filter(isGoalCountGreater));
        break;
    }
    case 6: {
        compareVal = promptIntegerInput("Enter a goal count:\n> ");
        printNamesList(ht.filter(isGoalCountLess));
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

bool namesClashFoldFunc(const Player& cur, bool accum) {
    return(contextPlayer.name == cur.name || accum);
}

bool isGoalCountEqual(const Player& p) {
    return p.goalcount == compareVal;
}

bool isGoalCountGreater(const Player& p) {
    return p.goalcount > compareVal;
}

bool isGoalCountLess(const Player& p) {
    return p.goalcount < compareVal;
}

void printNamesList(const List<Player>& l) {
    l.traversePrint(printName, ", ");
}

void printName(const Player& p) {
    std::cout << p.name;
}

void printPlayer(const Player& p) {
    std::cout << p;
}


