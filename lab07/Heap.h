#ifndef HEAP_H
#define HEAP_H

enum HeapType {MIN, MAX};

template <typename T>
class Heap {
    private:
        // Array to hold objects
        T* arr;

        // Number of children of each node
        // Children indeces range from 0 <= j <= k-1 for all k >= 2
        int k;

        // Number of objects currently in heap
        int n;

        int arr_size;
        HeapType type;

    protected:
        // Swaps indeces i, j in arr (if possible)
        bool swap(int i, int j);

        // Moves last element into arr[i] (if possible)
        bool move(int i, int j);
        int next_index() const;

        bool is_empty(int i) const;
        bool is_leaf(int i) const;
        bool is_root(int i) const;
        int jth_child(int i, int j) const; // Check to ensure not out of bounds
        int parent(int i) const; // Check to ensure not out of bounds

        // Child index (j) of child with highest priority
        int favorable_child(int i) const;

        // Child index (j) of child with highest priority
        // AND higher priority than parent (at index i)
        int switcher_child(int i) const;

        // returns true if the first argument displays 
        // is higher priority under this heap type
        // if type == MIN, returns true if arr[i1] <= arr[i2]
        // if type == MAX, returns true if arr[i1] >= arr[i2]
        // if one of the indeces is invalid (or both), returns true
        bool compare(int i1, int i2) const;

        // If type == MIN, then returns true if arr[i] <= arr[jth_child_index(i, j)]
        // If type == MAX, then returns true if arr[i] >= arr[jth_child_index(i, j)]
        // Essentially, returns true if correct heap order between 2 objects, otherwise false
        // param i = index, k = kth child of node at index i
        bool compare_child(int i, int j) const;

        // If not satisfying heap property, find (least/greatest) child
        // to swap with, and then percolate_down from new index
        // Used to build bottom-up (use at each level)
        void percolate_down(int i);

        // If type == MIN, returns true if arr[i] >= arr[parent(i)]
        // If type == MAX, returns true if arr[i] <= arr[parent(i)]
        // always returns true if root
        bool compare_parent(int i) const;

        // If not satisfying heap property, swap with parent
        // and then percolate_up from parent index
        // Used to build top-down
        void percolate_up(int i);

        // performed after the delete operation
        // returns the absolute index of the empty space
        // left open
        int fill_recursive(int i);

        // Checks to see whether obj is a duplicate of some
        // object already in the heap
        bool is_duplicate(const T& obj);

    public:
        Heap<T>(HeapType t, int num_children, int max_objects);
        ~Heap<T>();
        bool isEmpty() const;
        int size() const;
        bool insert(const T& obj);
        bool deleteItem(const T& obj);

        // What position in line is this object?
        // == arr index + 1
        int tokenOf(const T& obj);

        T peekFront() const;
        bool deleteFront();
        T popFront();

        // Given an array of elements and the number of items,
        // construct heap using bottom-up approach
        bool constructBottomUp(T* array, int numitems);
};

#endif