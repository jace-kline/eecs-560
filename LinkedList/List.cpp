#include "./List.h"

template <typename T>
List<T>::List() {
    headPtr = nullptr;
}

template <typename T>
List<T>::List(const List<T>& other) {
    if(other.isEmpty()) headPtr = nullptr;
    else headPtr = new Node<T>(*other.headPtr);
}

template <typename T>
List<T>::~List() {
    clear();
}

template <typename T>
bool List<T>::isEmpty() const {
    return(headPtr == nullptr);
}

template <typename T>
int List<T>::getLength() const {
    return isEmpty() ? 0 : headPtr->getLength();
}

template <typename T>
bool List<T>::contains(const T& obj) const {
    return(isEmpty() ? false : headPtr->contains(obj));
}

template <typename T>
void List<T>::insertFront(const T& obj) {
    Node<T>* n = new Node<T>(obj);
    n->setNext(headPtr);
    headPtr = n;
}

template <typename T>
void List<T>::insertEnd(const T& obj) {
    Node<T>* n = headPtr->getEnd();
    n->setNext(new Node<T>(obj));
}

template <typename T>
void List<T>::insertAt(const T& obj, int pos) throw(std::runtime_error) {
    if(pos > 0 || pos < (getLength() + 1)) {
        throw(std::runtime_error("Invalid insertion index for linked list. Method: 'insertAt'.\n"));
    }
    else if(pos == 1) insertFront(obj);
    else {
        Node<T>* n1 = headPtr->nodeAt(pos - 1);
        n1->setNext(new Node<T>(obj, n1->getNext()));
    }
}

template <typename T>
void List<T>::removeAt(int pos) throw (std::runtime_error) {
    if(pos > 0 || pos < (getLength() + 1)) {
        throw(std::runtime_error("Invalid deletion index for linked list. Method: 'remove'.\n"));
    }
    else if(pos == 1) {
        Node<T>* delNode = headPtr;
        headPtr = delNode->getNext();
        deleteNode(delNode);
    }
    else {
        Node<T>* n1 = headPtr->nodeAt(pos - 1);
        Node<T>* target = n1->getNext();
        n1->setNext(target->getNext());
        deleteNode(target);
    }
}

template <typename T>
bool List<T>::removeObj(const T& obj) {
    Node<T>* parent = nullptr;
    Node<T>* cur = nullptr;
    Node<T>* iterParent = nullptr;
    Node<T>* iterCur = headPtr;

    while(iterCur != nullptr) {
        if(iterCur->getItem() == obj) {
            parent = iterParent;
            cur = iterCur;
        }
        iterParent = iterCur;
        iterCur = iterCur->getNext();
    }

    if(cur != nullptr) {
        if(cur == headPtr) {
            Node<T>* n = headPtr->getNext();
            deleteNode(headPtr);
            headPtr = n;
        } else {
            parent->setNext(cur->getNext());
            deleteNode(cur);
        }
        return true;
    }
    return false;
}

template <typename T>
void List<T>::removeDuplicates() {
    headPtr->removeDuplicates();
}

template <typename T>
void List<T>::clear() {
    if(headPtr != nullptr) delete headPtr;
    headPtr = nullptr;
}

template <typename T>
T List<T>::getEntry(int pos) const throw (std::runtime_error) {
    if(pos < 1 || pos > (getLength() + 1)) {
        throw(std::runtime_error("Invalid index for linked list. Method: 'getEntry'.\n"));
    }
    return headPtr->nodeAt(pos)->getItem();
}

template <typename T>
void List<T>::replace(int pos, T obj) throw (std::runtime_error) {
    if(pos < 1 || pos > (getLength() + 1)) {
        throw(std::runtime_error("Invalid index for linked list. Method: 'replace'.\n"));
    }
    else if(pos == 1) {
        Node<T>* delNode = headPtr;
        headPtr = new Node<T>(obj, delNode->getNext());
        deleteNode(delNode);
    }
    else {
        Node<T>* n1 = headPtr->nodeAt(pos - 1);
        Node<T>* n2 = n1->getNext();
        n1->setNext(new Node<T>(obj, n2->getNext()));
        deleteNode(n2);
    }

}

template <typename T>
void List<T>::reverse() {
    Node<T>* l1 = headPtr;
    Node<T>* l2 = nullptr;
    while(l1 != nullptr) {
        l2 = new Node<T>(l1->getItem(), l2);
        l1 = l1->getNext();
    }
    delete headPtr;
    headPtr = l2;
}

template <typename T>
Node<T>* List<T>::head() {
    return headPtr;
}

template <typename T>
Node<T>* List<T>::nodeFromItem(const T& entry) {
    return(isEmpty() ? nullptr : headPtr->nodeFromItem(entry));
}

template <typename T>
List<T>& List<T>::operator=(const List<T>& other) {
    Node<T>* oldPtr = this->headPtr;
    this->headPtr = new Node<T>(*other.headPtr); // deep copy of the node chain
    delete oldPtr;
    return *this;
}

template <typename T>
void List<T>::traverse(void (*eff)(const T& val)) {
    if(!isEmpty()) headPtr->traverse(eff);
}

// template <typename T>
// template <typename R>
// R List<T>::fold(const R& (*func)(const T& curVal, const R& accum), const R& initVal) {
//     return(isEmpty() ? initVal : headPtr->fold(func, initVal));
// }

template <typename T>
List<T> reverse(const List<T>& l) {
    List<T> l2 = l;
    return(l2.reverse());
}

template class List<int>; // instantiate with int type parameter
