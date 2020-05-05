#include "Heap.h"

template <typename T>
Heap<T>::Heap(HeapType t, int num_children, int max_objects) {
    arr = new T[max_objects];
    k = num_children;
    type = t;
    n = 0;
}

template <typename T>
Heap<T>::~Heap() {
    if(arr != nullptr) delete[] arr;
}

template <typename T>
bool Heap<T>::swap(int i, int j) {
    if(is_empty(i) || is_empty(j)) return false;
    T tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
    return true;
}

template <typename T>
int Heap<T>::next_index() const {
    return n;
}

template <typename T>
bool Heap<T>::is_empty(int i) const  {
    return (i >= n || i < 0);
}

template <typename T>
bool Heap<T>::is_leaf(int i) const {
    return(jth_child(i, 1) >= n);
}

template <typename T>
bool Heap<T>::is_root(int i) const {
    return(i == 0);
}

template <typename T>
int Heap<T>::jth_child(int i, int j) const {
    if(j < 1 || j > k) return -1;
    return(k * i + j);
}

template <typename T>
int Heap<T>::parent(int i) const {
    return(floor((i - 1) / k));
}

template <typename T>
int Heap<T>::favorable_child(int i) const {
    if(is_empty(i) || is_leaf(i)) return -1;
    int candidate = -1;
    for(int j = 1; j <= k; j++) {
        if(candidate == -1) candidate = (jth_child(i, j) != -1 ? j : -1);
        if(compare(jth_child(i, j), jth_child(i, candidate))) candidate = j;
    }
    return candidate;
}

template <typename T>
int Heap<T>::switcher_child(int i) const {
    if(is_empty(i) || is_leaf(i)) return -1;
    int candidate = favorable_child(i);
    return !compare_child(i, candidate) ? candidate : -1;
}

template <typename T>
bool Heap<T>::compare(int i1, int i2) const {
    if(is_empty(i2)) return true;
    if(is_empty(i1)) return false;
    if(type == MIN) return arr[i1] <= arr[i2];
    else return arr[i1] >= arr[i2];
}

template <typename T>
bool Heap<T>::compare_child(int i, int j) const {
    if(is_empty(i) || is_empty(jth_child(i, j))) return true;
    if(type == MIN) return arr[i] <= arr[jth_child(i, j)];
    else return arr[i] >= arr[jth_child(i, j)];
}

template <typename T>
bool Heap<T>::compare_parent(int i) const {
    if(is_empty(i) || is_empty(parent(i))) return true;
    if(type == MIN) return arr[parent(i)] <= arr[i];
    else return arr[parent(i)] >= arr[i];
}

template <typename T>
void Heap<T>::percolate_down(int i) {
    if(is_empty(i) || is_leaf(i)) return;
    int j = jth_child(i, switcher_child(i));
    if(j != -1) {
        swap(i, j);
        percolate_down(j);
    }
}

template <typename T>
void Heap<T>::percolate_up(int i) {
    if(is_empty(i)) return;
    if(!compare_parent(i)) {
        swap(i, parent(i));
        percolate_up(parent(i));
    }
}

template <typename T>
int Heap<T>::fill_recursive(int i) {
    if(is_empty(i)) return -1; // error
    if(is_leaf(i)) return i; // base case
    int fill_index = jth_child(i, favorable_child(i));
    if(fill_index == -1) return -1;
    arr[i] = arr[fill_index]; // fill the empty space
    return(fill_recursive(fill_index));
}

template <typename T>
bool Heap<T>::is_duplicate(const T& obj) {
    for(int i = 0; i < n; i++) {
        if(obj == arr[i]) return true;
    }
    return false;
}

template <typename T>
T Heap<T>::itemAtSorted(int r) {
    if(r < 0 || r >= n) throw(std::runtime_error("Invalid array index."));
    T a[n];

    // copy arr values
    for(int i = 0; i < n; i++) {
        a[i] = arr[i];
    }

    // sort
    for(int j = 0; j < n - 1; j++) {
        for(int i = 0; i < n-j-1; i++) {
            if(type == MIN ? a[i] > a[i+1] : a[i] < a[i+1]) {
                T tmp = a[i];
                a[i] = a[i+1];
                a[i+1] = tmp;
            } 
        }
    }
    return a[r];
}

template <typename T>
int Heap<T>::tokenOfSorted(const T& obj) {
    T a[n];

    // copy arr values
    for(int i = 0; i < n; i++) {
        a[i] = arr[i];
    }

    // sort
    for(int j = 0; j < n - 1; j++) {
        for(int i = 0; i < n-j-1; i++) {
            if(type == MIN ? a[i] > a[i+1] : a[i] < a[i+1]) {
                T tmp = a[i];
                a[i] = a[i+1];
                a[i+1] = tmp;
            } 
        }
    }

    // find element (or -1 if not found)
    for(int i = 0; i < n; i++) {
        if(a[i] == obj) return(i + 1);
    }
    return(-1);
}

template <typename T>
bool Heap<T>::isEmpty() const {
    return(n == 0);
}

template <typename T>
int Heap<T>::size() const {
    return n;
}

template <typename T>
bool Heap<T>::insert(const T& obj) {
    if(!is_duplicate(obj)) {
        n++;
        arr[n-1] = obj;
        percolate_up(n-1);
        return true;
    }
    return false;
}

template <typename T>
bool Heap<T>::addNoHeapify(const T& obj) {
    if(is_duplicate(obj)) return false;
    else {
        arr[n] = obj;
        n++;
    }
    return true;
}

template <typename T>
bool Heap<T>::deleteItem(const T& obj) {
    for(int i = 0; i < n; i++) {
        if(arr[i] == obj) {
            int index = fill_recursive(i);
            if(index != -1) {
                arr[index] = arr[n-1];
                n--;
                percolate_up(n-1);
                return true;
            }
        }
    }
    return false; // item not found
}

template <typename T>
int Heap<T>::tokenOf(const T& obj) {
    for(int i = 0; i < n; i++) {
        if(arr[i] == obj) return(i + 1);
    }
    return -1; // not found
}

template <typename T>
T Heap<T>::itemAt(int i) {
    if(is_empty(i)) throw(std::runtime_error("Invalid array index access."));
    return(arr[i]);
}

template <typename T>
T Heap<T>::peekFront() const {
    if(isEmpty()) throw(std::runtime_error("Attempted to peek an empty heap."));
    return(arr[0]);
}

template <typename T>
T Heap<T>::peekLast() const {
    if(isEmpty()) throw(std::runtime_error("Attempted to peek an empty heap."));
    return(arr[n-1]);
}

template <typename T>
bool Heap<T>::deleteFront() {
    if(isEmpty()) throw(std::runtime_error("Attempted to delete from an empty heap."));
    int index = fill_recursive(0);
    if(index != -1) {
        arr[index] = arr[n-1];
        n--;
        percolate_up(n-1);
        return true;
    } else return false; // error
}

template <typename T>
T Heap<T>::popFront() {
    T item = peekFront();
    deleteFront();
    return item;
}

template <typename T>
void Heap<T>::constructBottomUp() {
    // Loop through in reverse-level order from right to left
    // and percolate down
    for(int i = n - 1; i >= 0; i--) {
        percolate_down(i);
    }
}

template class Heap<int>;
template class Heap<WEdge>;