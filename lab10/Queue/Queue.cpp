#include "Queue.h"

template <typename T>
Queue<T>::Queue() {}

template <typename T>
Queue<T>::~Queue() {}

template <typename T>
bool Queue<T>::isEmpty() const {
    return list.isEmpty();
}

template <typename T>
int Queue<T>::size() const {
    return list.getLength();
}

template <typename T>
void Queue<T>::enqueue(const T& x) {
    return list.insertEnd(x);
}

template <typename T>
T Queue<T>::dequeue() {
    T ret = peek();
    list.removeAt(1);
    return ret;
}

template <typename T>
T Queue<T>::peek() {
    if(isEmpty()) throw std::runtime_error("Error. Access performed on empty queue.");
    else return list.getEntry(1);
}

template class Queue<int>;
template class Queue<WEdge>;