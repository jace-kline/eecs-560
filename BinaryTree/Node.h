#ifndef NODE_H
#define NODE_H

template <typename T>
class Node {
    private:
        T item;
        Node<T>* left;
        Node<T>* right;

    protected:
        Node<T>* farRightLeaf();
    
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
        void setItem(const T& obj);
        void setLeft(Node<T>* l);
        void setRight(Node<T>* r);
        void traversePreorder(void (*eff)(const T&)) const;
        void traversePostorder(void (*eff)(const T&)) const;
        void traverseInorder(void (*eff)(const T&)) const;
};

#endif