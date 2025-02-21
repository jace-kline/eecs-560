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
        int l = left == nullptr ? 0 : left->traverseLeftSideHelp(eff, t-1);
        int r = right == nullptr ? 0 : right->traverseLeftSideHelp(eff, (l > t - 1 ? l : t - 1));
        return(1 + (r > l ? r : l));
    }
}

template <typename T>
int Node<T>::traverseRightSideHelp(void (*eff)(const T&), int t) const {
    if(t <= 0) eff(item);
    if(isLeaf()) return 1;
    else {
        int r = right == nullptr ? 0 : right->traverseRightSideHelp(eff, t-1);
        int l = left == nullptr ? 0 : left->traverseRightSideHelp(eff, (r > t - 1 ? r : t - 1));
        return(1 + (l > r ? l : r));
    }
}

template <typename T>
T Node<T>::inorderSuccessor(const T& obj) const {
    Maybe<T> m;
    inorder_struct<T> init = inorder_struct<T> {obj, m, false};
    inorder_struct<T> ret = foldInorder(inorderSuccFoldFunc, init);
    if(!ret.is_found || !ret.succ.exists) throw(std::runtime_error("Given element was not found or has no successor."));
    return(ret.succ.item);
}

template <typename T>
T Node<T>::kthUniqueItem(int k) const {
    if(k < 1) throw(std::runtime_error("List index error. k-value too small."));
    Maybe<T> m;
    kth_struct<T> init = kth_struct<T> {k, 0, m};
    kth_struct<T> ret = foldInorder(kthItemFoldFunc, init);
    if(ret.target_k != ret.current_k) throw(std::runtime_error("List index error. k-value too large."));
    return(ret.val.item);
}

template <typename T>
template <typename R>
R Node<T>::foldInorder(R (*f)(R, const T&), R i) const {
    R left_return = left == nullptr ? i : left->foldInorder(f, i);
    R node_result = f(left_return, item);
    return(right == nullptr ? node_result : right->foldInorder(f, node_result));
}

template <typename T>
inorder_struct<T> inorderSuccFoldFunc(inorder_struct<T> prev, const T& obj) {
    if(prev.is_found) {
        if(prev.succ.exists) return prev;
        else {
            Maybe<T> m = Maybe<T>(obj);
            return(inorder_struct<T> {prev.target_obj, m, true});
        }
    } else if(obj == prev.target_obj) {
        Maybe<T> m;
        return(inorder_struct<T> {prev.target_obj, m, true});
    }
    return(prev);
}

template <typename T>
kth_struct<T> kthItemFoldFunc(kth_struct<T> prev, const T& obj){
    if(prev.target_k == prev.current_k) return prev;
    else {
        int new_k = prev.val.item == obj ? prev.current_k : prev.current_k + 1;
        return(kth_struct<T> {prev.target_k, new_k, obj});
    }
}

template <typename T>
Maybe<T>::Maybe() {
    exists = false;
}

template <typename T>
Maybe<T>::Maybe(const T& obj) {
    exists = true;
    item = obj;
}

template <typename T>
Maybe<T>::~Maybe() {}

template class Node<int>;
template class Maybe<int>;
template struct inorder_struct<int>;
template struct kth_struct<int>;