#include "Node.h"

template <typename T>
Node<T>::Node(const T& obj) {
    item = obj; // Must overload equality for type T
    left = nullptr;
    right = nullptr;
}

template <typename T>
Node<T>::Node(const T& obj, Node<T>* l, Node<T>* r) {
    item = obj;
    // Recursively use the copy constructor on children nodes
    left = (l == nullptr ? nullptr : new Node<T>(*l));
    right = (r == nullptr ? nullptr : new Node<T>(*r));
}

template <typename T>
Node<T>::Node(const Node<T>& other) {
    item = other.item;
    left = (other.left == nullptr ? nullptr : new Node<T>(*other.left));
    right = (other.right == nullptr ? nullptr : new Node<T>(*other.right));
}

template <typename T>
Node<T>::~Node() {
    if(left != nullptr) delete left;
    if(right != nullptr) delete right;
}

template <typename T>
void Node<T>::doLevel(void (*eff)(const T& obj), int level) const {
    if(level == 0) eff(item);
    else {
        if(left != nullptr) left->doLevel(eff, level - 1);
        if(right != nullptr) right->doLevel(eff, level - 1);
    }
}

template <typename T>
void Node<T>::doReverseLevel(void (*eff)(const T& obj), int level) const {
    if(level == 0) eff(item);
    else {
        if(right != nullptr) right->doReverseLevel(eff, level - 1);
        if(left != nullptr) left->doReverseLevel(eff, level - 1);
    }
}

// template <typename T>
// void Node<T>::doLevelIfLeaf(void (*eff)(const T& obj), int level) const {
//     if(level == 0 && isLeaf()) eff(item);
//     else {
//         if(left != nullptr) left->doLevel(eff, level - 1);
//         if(right != nullptr) right->doLevel(eff, level - 1);
//     }
// }

template <typename T>
bool Node<T>::add(const T& obj) {
    if(obj < item) {
        if(left == nullptr) {
            left = new Node<T>(obj);
            return true;
        }
        else return(left->add(obj));
    } else {
        if(right == nullptr) {
            right = new Node<T>(obj);
            return true;
        }
        else return(right->add(obj));
    }
    return false;
}

template <typename T>
bool Node<T>::remove(const T& obj) {
    if(obj < item) {
        if(left == nullptr) return false;
        else if(left->item == obj) {
            left = removeHelper(left);
            return true;
        }
        else return(left->remove(obj));
    } else {
        if(right == nullptr) return false;
        else if(right->item == obj) {
            right = removeHelper(right);
            return true;
        }
        else return(right->remove(obj));
    }
}

template <typename T>
Node<T>* Node<T>::removeHelper(Node<T>* target) {
    Node<T>* p = nullptr;
    if(target->isLeaf()) delete target;
    else if(target->left == nullptr) {
        p = target->right;
    } else if(target->right == nullptr) {
        p = target->left;
    } else {
        Node<T>* parent = target->right;
        if(parent->left == nullptr) {
            p = target->right;
            p->left = target->left;
        } else {
            p = parent->left;
            while(p->left != nullptr) {
                parent = p;
                p = p->left;
            }
            parent->left = p->right;
            p->left = target->left;
            p->right = target->right; 
        }
    }
    target->right = nullptr;
    target->left = nullptr;
    delete target;
    return p;
}


// template <typename T>
// template <typename R>
// bool Node<T>::anyNodesSatisfy(bool (*p)(Node<T>*, R), R x) {
//     return(p(this, x) ? true : (left == nullptr ? false : left->anyNodesSatisfy<std::string>(p, x)) || (right == nullptr ? false : right->anyNodesSatisfy<std::string>(p, x)));
// }

// template <typename T>
// T Node<T>::popLastLeaf() {
//     if(isLeaf()) throw(std::runtime_error("Error. Can't pop from context of a leaf node.\n"));
//     int l_nodes = left == nullptr ? 0 : left->numNodes();
//     int r_nodes = right == nullptr ? 0 : right->numNodes();
//     if(r_nodes >= l_nodes) {
//         if(r_nodes == 1) {
//             T val = right->getItem();
//             delete right;
//             right = nullptr;
//             return val;
//         } else return(right->popLastLeaf());
//     } else {
//         if(l_nodes == 1) {
//             T val = left->getItem();
//             delete left;
//             left = nullptr;
//             return val;
//         } else return(left->popLastLeaf());
//     } 
// }

template <typename T>
bool Node<T>::isLeaf() const {
    return (left == nullptr && right == nullptr);
}

template <typename T>
int Node<T>::height() const {
    if(isLeaf()) return 0;
    else {
        int lheight = (left == nullptr ? 0 : left->height());
        int rheight = (right == nullptr ? 0 : right->height());
        return(1 + (lheight > rheight ? lheight : rheight));
    }
}

template <typename T>
bool Node<T>::isFull() const {
    return(isLeaf() ? true : 
          (left == nullptr || right == nullptr ? false : 
          left->isFull() && right->isFull() && left->height() == right->height()));
}

template <typename T>
T Node<T>::getItem() const {
    return item;
}

template <typename T>
Node<T>* Node<T>::getLeft() {
    return left;
}

template <typename T>
Node<T>* Node<T>::getRight() {
    return right;
}

template <typename T>
int Node<T>::numNodes() const {
    if(isLeaf()) return 1;
    return(1 + (left == nullptr ? 0 : left->numNodes()) + (right == nullptr ? 0 : right->numNodes()));
}

template <typename T>
void Node<T>::setItem(const T& obj) {
    item = obj;
}

template <typename T>
void Node<T>::setLeft(Node<T>* l) {
    if(left != nullptr) delete left;
    left = l;
}

template <typename T>
void Node<T>::setRight(Node<T>* r) {
    if(right != nullptr) delete right;
    right = r;
}

// template <typename T>
// void Node<T>::traversePreorder(void (*eff)(const T&)) const {
//     eff(item);
//     if(left != nullptr) left->traversePreorder(eff);
//     if(right != nullptr) right->traversePreorder(eff);
// }

// template <typename T>
// void Node<T>::traversePostorder(void (*eff)(const T&)) const {
//     if(left != nullptr) left->traversePostorder(eff);
//     if(right != nullptr) right->traversePostorder(eff);
//     eff(item);
// }

template <typename T>
void Node<T>::traverseInorder(void (*eff)(const T&)) const {
    if(left != nullptr) left->traverseInorder(eff);
    eff(item);
    if(right != nullptr) right->traverseInorder(eff);
}

template <typename T>
void Node<T>::traverseLevel(void (*eff)(const T&)) const {
    for(int i = 0; i <= height(); i++) {
        doLevel(eff, i);
    }
}

template <typename T>
void Node<T>::traverseSpiralLevel(void (*eff)(const T&)) const {
    for(int i = 0; i <= height(); i++) {
        if(i % 2 == 0) doLevel(eff, i);
        else doReverseLevel(eff, i);
    }
}

template <typename T>
void Node<T>::traverseLeftSide(void (*eff)(const T&)) const {
    traverseLeftSideHelp(eff, 0);
}

template <typename T>
void Node<T>::traverseRightSide(void (*eff)(const T&)) const {
    traverseRightSideHelp(eff, 0);
}

template <typename T>
int Node<T>::traverseLeftSideHelp(void (*eff)(const T&), int t) const {
    if(t <= 0) eff(item);
    if(isLeaf()) return 1;
    else {
        int l = left == nullptr ? 0 : 1 + left->traverseLeftSideHelp(eff, t-1);
        int r = right == nullptr ? 0 : 1 + right->traverseLeftSideHelp(eff, l);
        return(l > r ? l : r);
    }
}

template <typename T>
int Node<T>::traverseRightSideHelp(void (*eff)(const T&), int t) const {
    if(t <= 0) eff(item);
    if(isLeaf()) return 1;
    else {
        int r = right == nullptr ? 0 : 1 + right->traverseRightSideHelp(eff, t-1);
        int l = left == nullptr ? 0 : 1 + left->traverseRightSideHelp(eff, r);
        return(l > r ? l : r);
    }
}

template <typename T>
ListNode<T>* Node<T>::toInorderListHelper() const {
    if(isLeaf()) return(new ListNode<T>(item));
    else {
        ListNode<T>* prev = left == nullptr ? nullptr : left->toInorderListHelper().last();
        ListNode<T>* rest = right == nullptr ? nullptr : right->toInorderListHelper().head();
        return(new ListNode<T>(item, prev, rest));
    }
}

template <typename T>
ListNode<T>* Node<T>::toInorderList() const {
    return(toInorderListHelper().head());
}

template <typename T>
T Node<T>::inorderSuccessor(const T& obj) {
    ListNode<T>* l = toInorderList();
    ListNode<T>* p = l->inorderSuccessorPtr(obj);
    if(p == nullptr) throw(std::runtime_error("No successor to highest priority item."));
    else {
        T x = p->item;
        delete l;
        return x;
    }
}

template <typename T>
T Node<T>::getKthUniqueItem(int k) const {
    if(k < 1) throw(std::runtime_error("List index error. k-value too small."));
    ListNode<T>* l = toInorderList();
    ListNode<T>* p = l->kthUniqueItemPtr(k);
    if(p == nullptr) throw(std::runtime_error("List index error. k-value too large."));
    else {
        T x = p->item;
        delete l;
        return x;
    }
}

template <typename T>
ListNode<T>::ListNode(const T& obj) : item(obj), prev(nullptr), next(nullptr) {}

template <typename T>
ListNode<T>::ListNode(const T& obj, ListNode<T>* p, ListNode<T>* n) : item(obj), prev(p), next(n) {}

template <typename T>
ListNode<T>::~ListNode() {
    if(next != nullptr) delete next;
}

template <typename T>
T ListNode<T>::at(int i) const {
    if(i == 1) return item;
    else if(next != nullptr) return next->at(i - 1);
    else throw(std::runtime_error("Invalid index for list access."));
}

template <typename T>
ListNode<T>* ListNode<T>::head() {
    return(prev == nullptr ? this : prev->head());
}

template <typename T>
ListNode<T>* ListNode<T>::last() {
    return(next == nullptr ? this : next->last());
}

template <typename T>
ListNode<T>* ListNode<T>::kthUniqueItemPtr(int k) {
    if(k == 1) return this;
    else if(k > 1) {
        return(next->kthUniqueItemPtr((prev == nullptr || prev->item != item) ? k - 1 : k));
    }
}

template <typename T>
ListNode<T>* ListNode<T>::inorderSuccessorPtr(const T& obj) {
    if(item == obj) return next;
    else return(next == nullptr ? nullptr : next->inorderSuccessorPtr(obj));
}
// template <typename T>
// void Node<T>::traverseLeavesLevel(void (*eff)(const T&)) const {
//     for(int i = 0; i <= height(); i++) {
//         doLevelIfLeaf(eff, i);
//     }
// }

template class ListNode<int>;
template class Node<int>;