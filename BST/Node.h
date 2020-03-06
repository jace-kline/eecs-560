#ifndef NODE_H
#define NODE_H

#include <stdexcept>

// Type T must have <, >, <=, >=, == operators defined
template <typename T>
class Node {
    private:
        T item;
        Node<T>* left;
        Node<T>* right;

    protected:
        void doLevel(void (*eff)(const T&), int level) const;
        void doReverseLevel(void (*eff)(const T&), int level) const;
        int traverseLeftSideHelp(void (*eff)(const T&), int threshold) const;
        int traverseRightSideHelp(void (*eff)(const T&), int threshold) const;
        Node<T>* removeHelper(Node<T>* target);

    public:
        Node<T>(const T& obj);
        Node<T>(const T& obj, Node<T>* l, Node<T>* r);
        Node<T>(const Node<T>& other);
        ~Node<T>();
        
        bool isLeaf() const;
        int height() const;
        bool isFull() const;
        T getItem() const;
        Node<T>* getLeft();
        Node<T>* getRight();
        int numNodes() const;
        bool add(const T& obj);
        bool remove(const T& obj);

        void setItem(const T& obj);
        void setLeft(Node<T>* l);
        void setRight(Node<T>* r);
        void traverseInorder(void (*eff)(const T&)) const;
        void traverseLevel(void (*eff)(const T&)) const;
        void traverseSpiralLevel(void (*eff)(const T&)) const;
        void traverseLeftSide(void (*eff)(const T&)) const;
        void traverseRightSide(void (*eff)(const T&)) const;
        T inorderSuccessor(const T& obj) const;
        T kthUniqueItem(int k) const;

        template <typename R>
        R foldInorder(R (*f)(R, const T&), R) const;
};

template <typename T>
class Maybe {
    public:
        bool exists;
        T item;
        Maybe();
        Maybe(const T&);
        ~Maybe();
};

template <typename T>
struct inorder_struct {
    T target_obj;
    Maybe<T> succ;
    bool is_found;
};

template <typename T>
struct kth_struct {
    int target_k;
    int current_k;
    Maybe<T> val;
};

template <typename T>
inorder_struct<T> inorderSuccFoldFunc(inorder_struct<T> prev, const T& obj);

template <typename T>
kth_struct<T> kthItemFoldFunc(kth_struct<T> prev, const T& obj);

#endif