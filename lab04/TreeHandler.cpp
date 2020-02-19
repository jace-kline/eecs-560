#include "TreeHandler.h"

TreeHandler::TreeHandler() {}

TreeHandler::~TreeHandler() {}

void TreeHandler::fillTreeFromFile(std::string filename) {
    std::ifstream fs;
    std::string title;
    char comma;
    float rating;
    Movie m;
    fs.open(filename);
    while(fs.peek() != EOF) {
        fs >> title;
        if(title.back() == ',') title.pop_back();
        else fs >> comma;
        fs >> rating;
        if(isValidRating(rating)) {
            m.title = title;
            m.rating = rating;
            tree.add(m);
        }
    }
    fs.close();
}

void TreeHandler::isFull() const {
    std::cout << "Is Full?: " << (tree.isFull() ? "True" : "False") << '\n';
}

void TreeHandler::addMovie(const Movie& m) {
    if(tree.add(m)) std::cout << "Movie added successfully!\n";
    else std::cout << "Error. Movie could not be added to the tree.\n";
}

void TreeHandler::removeLastMovie() {
    try {
        Movie m = tree.popLastLeaf();
        std::cout << "The last movie, with title " << m.title << " and rating " << m.rating << ", has been deleted.\n";
    } catch(std::runtime_error& e) {
        std::cout << e.what() << '\n';
    }
}

void TreeHandler::isTitleLeaf(std::string title) {
    std::cout << "The title '" << title << "' " << (tree.anyNodesSatisfy(isLeafFunc, title) ? "is" : "is not") << " a leaf node.\n";
}

void TreeHandler::printLeaves() const {
    std::cout << "Printing Leaves: ";
    tree.traverseLeavesLevel(printTitle);
    std::cout << '\n';
}

void TreeHandler::printTreeHeight() const {
    std::cout << "Tree Height: " << tree.height() << '\n';
}

void TreeHandler::preorderRatings() const {
    std::cout << "Print Ratings (Preorder): ";
    tree.traversePreorder(printRating);
    std::cout << '\n';
}

void TreeHandler::postorderRatings() const {
    std::cout << "Print Ratings (Postorder): ";
    tree.traversePostorder(printRating);
    std::cout << '\n';
}

void TreeHandler::inorderRatings() const {
    std::cout << "Print Ratings (Inorder): ";
    tree.traverseInorder(printRating);
    std::cout << '\n';
}

void TreeHandler::levelTitles() const {
    std::cout << "Print Titles (Level order): ";
    tree.traverseLevel(printTitle);
    std::cout << '\n';
}

bool isLeafFunc(Node<Movie>* n, std::string title) {
    return((n->getItem().title == title) && n->isLeaf());
}

void printTitle(const Movie& m) {
    std::cout << m.title << ", ";
}

void printRating(const Movie& m) {
    std::cout << m.rating << ", ";
}


