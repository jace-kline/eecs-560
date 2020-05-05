#ifndef QUEUE_H
#define QUEUE_H

#include "../List/List.h"
#include "../Graph/WEdge.h"

template <typename T>
class Queue {
    private:
        List<T> list;
    public:
        Queue<T>();
        ~Queue<T>();
        bool isEmpty() const;
        int size() const;
        void enqueue(const T& x);
        T dequeue();
        T peek();
};

#endif