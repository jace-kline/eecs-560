#ifndef MAXMIN_H
#define MAXMIN_H

#include <stdexcept>
#include <cmath>
#include "Game.h"

enum LevelType {MIN, MAX, ERR};

template <typename T>
class Heap {
    private:
        T* arr;
        int max_size;
        int k; // Number of children per node
        int n; // Number of elements in heap

    protected:
        bool is_root(int i) const;
        bool is_invalid(int i) const;

        bool compare(int i, int j) const;

        int jth_child(int i, int j) const;
        int parent(int i) const;
        int grandparent(int i) const;
        int min_index_grandchild(int i) const;
        int max_index_grandchild(int i) const;

        LevelType level_type(int i) const;
        int level(int i) const;
        int next_of_level_type(int i) const;
        
        int is_duplicate(const T& obj) const;

        bool swap(int i, int j);

        int swapper_child(int i) const;
        int swapper_grandchild(int i) const;

        void percolate_up(int i);
        void percolate_down(int i);

        bool delete_index(int i);

        int min_index() const;

        void traverseLevelsHelp(int i, LevelType, void (*f)(const T&)) const;

        template <typename R>
        R foldLevelsHelp(int i, LevelType, R (*func)(const T&, R), R accum) const;

    public:
        Heap<T>(int childrenPerNode, int max_size);
        ~Heap<T>();

        bool isEmpty() const;

        bool add(const T& obj);

        bool deleteItem(const T& obj);
        bool deleteMin();
        bool deleteMax();

        T peekMin() const;
        T peekMax() const;

        void traverseLevels(LevelType, void (*f)(const T&)) const;

        void traverseAll(void (*f)(const T&)) const;

        template <typename R>
        R foldLevels(LevelType, R (*f)(const T&, R), R accum) const;
};

int power(int b, int e);

#endif