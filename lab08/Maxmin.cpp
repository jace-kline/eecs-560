#include "Maxmin.h"

template <typename T>
Heap<T>::Heap(int childrenPerNode, int msize) {
    max_size = msize;
    k = childrenPerNode;
    arr = new T[max_size];
    n = 0;
}

template <typename T>
Heap<T>::~Heap() {
    if(arr != nullptr) delete[] arr;
}

template <typename T>
bool Heap<T>::is_root(int i) const { return i == 0; }

template <typename T>
bool Heap<T>::is_invalid(int i) const { return (i < 0 || i >= n); }

template <typename T>
bool Heap<T>::compare(int i, int j) const {
    if(is_invalid(i) || is_invalid(j) || level(i) != level(j)) return false;
    else {
        LevelType t = level_type(i);
        if(t == MIN) return arr[i] < arr[j];
        else if (t == MAX) return arr[i] > arr[j];
    }
    return false;
}

template <typename T>
int Heap<T>::jth_child(int i, int j) const {
    return ((j < 0 || j >= k) ? -1 : k * i + j);
}

template <typename T>
int Heap<T>::parent(int i) const {
    return (is_root(i) || is_invalid(i) ? -1 : floor((i-1)/k));
}

template <typename T>
int Heap<T>::grandparent(int i) const {
    if(is_root(i) || is_root(parent(i))) return -1;
    else return parent(parent(i));
}

template <typename T>
int Heap<T>::min_index_grandchild(int i) const {
    int x = jth_child(jth_child(i,1),1);
    return (is_invalid(x) ? -1 : x);
}

template <typename T>
int Heap<T>::max_index_grandchild(int i) const {
    int x = jth_child(jth_child(i,k),k);
    return (!is_invalid(x) ? x : (min_index_grandchild(i) != -1 ? n - 1 : -1));
}

template <typename T>
LevelType Heap<T>::level_type(int i) const {
    if(level(i) == -1) return ERR;
    else return (level(i) % 2 == 0 ? MAX : MIN);
}


template <typename T>
int Heap<T>::level(int i) const {
    if(is_invalid(i)) return -1;
    else return(floor(log(i+1)/log(k)));
}

template <typename T>
int Heap<T>::next_of_level_type(int i) const {
    LevelType t = level_type(i);
    if(level_type(i+1) == t) return(i+1);
    else return(power(k, level(i) + 2) - 1);
}

template <typename T>
int Heap<T>::is_duplicate(const T& obj) const {
    for(int i = 0; i < n; i++) {
        if(arr[i] == obj) return true;
    }
    return false;
}

template <typename T>
bool Heap<T>::swap(int i, int j) {
    if(is_invalid(i) || is_invalid(j)) return false;
    else {
        T tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
        return true;
    }
}

template <typename T>
void Heap<T>::percolate_up(int i) {
    if(is_root(i) || is_invalid(i)) return;
    else if((level_type(i) == MIN && arr[i] > arr[parent(i)]) ||
        (level_type(i) == MAX && arr[i] < arr[parent(i)])) {
            swap(i, parent(i));
            percolate_up(parent(i));
    } else if(!is_invalid(grandparent(i))) {
        if ((level_type(i) == MIN && arr[i] < arr[grandparent(i)]) ||
        (level_type(i) == MAX && arr[i] > arr[grandparent(i)])) {
            swap(i, grandparent(i));
            percolate_up(grandparent(i));
        }
    }
}

template <typename T>
int Heap<T>::swapper_child(int i) const {
    int best_child = -1;
    for(int j = 1; j <= k; j++) {
        int cindex = jth_child(i,j);
        if(is_invalid(cindex)) break;
        else {
            if((level_type(cindex) == MIN && arr[cindex] > arr[i]) ||
               (level_type(cindex) == MAX && arr[cindex] < arr[i])) {
                   if(best_child == -1 || compare(cindex, best_child)) best_child = cindex;
               }
        }
    }
    return best_child;
}

template <typename T>
int Heap<T>::swapper_grandchild(int i) const {
    int min = min_index_grandchild(i);
    int max = max_index_grandchild(i);
    if(min == -1) return -1;
    int best_gc = -1;
    for(int j = min; j <= max; j++) {
        if(is_invalid(j)) break;
        if((level_type(i) == MIN && arr[j] < arr[i]) ||
            (level_type(i) == MAX && arr[j] > arr[i])) {
            if(best_gc == -1 || compare(j, best_gc)) best_gc = j;
        }
    }
    return best_gc;
}

template <typename T>
void Heap<T>::percolate_down(int i) {
    if(is_invalid(i)) return; // base case

    // recursive case
    int swap_index = swapper_child(i) != -1 ? swapper_child(i) : 
                     (swapper_grandchild(i) != -1 ? swapper_grandchild(i) : -1);
    if(swap_index != -1) {
        swap(swap_index, i);
        percolate_down(swap_index);
    }
}

template <typename T>
bool Heap<T>::delete_index(int i) {
    if(is_invalid(i)) return false;
    else if(n <= 1) n = 0;
    else {
        arr[i] = arr[n-1]; 
        n--;
        percolate_down(i);
    }
    return true;
}

template <typename T>
int Heap<T>::min_index() const {
    if(isEmpty()) return -1;
    else if(n == 1) return 0;
    else if(n == 2) return 1;
    else return (arr[1] < arr[2] ? 1 : 2);
}

template <typename T>
void Heap<T>::traverseLevelsHelp(int i, LevelType t, void (*f)(const T&)) const {
    if(i >= n) return; // base case
    else {
        f(arr[i]);
        traverseLevelsHelp(next_of_level_type(i), t, f);
    }
}

template <typename T>
void Heap<T>::traverseLevels(LevelType t, void (*f)(const T&)) const {
    return traverseLevelsHelp(t == MAX ? 0 : 1, t, f);
}

template <typename T>
void Heap<T>::traverseAll(void (*f)(const T&)) const {
    for(int i = 0; i < n; i++) {
        f(arr[i]);
    }
}

template <typename T>
template <typename R>
R Heap<T>::foldLevelsHelp(int i, LevelType t, R (*f)(const T&, R), R accum) const {
    if(i >= n) return accum; // base case
    return (foldLevelsHelp(next_of_level_type(i), t, f, f(arr[i], accum)));
}

template <typename T>
template <typename R>
R Heap<T>::foldLevels(LevelType t, R (*f)(const T&, R), R accum) const {
    return foldLevelsHelp(t == MAX ? 0 : 1, t, f, accum);
}

template <typename T>
bool Heap<T>::isEmpty() const {
    return(n == 0);
}

template <typename T>
bool Heap<T>::add(const T& obj) {
    // if(is_duplicate(obj)) return false;
    // else {
        arr[n] = obj;
        n++;
        percolate_up(n-1);
        return true;
    // }
}

template <typename T>
bool Heap<T>::deleteItem(const T& obj) {
    for(int i = 0; i < n; i++) {
        if(obj == arr[i]) return(delete_index(i));
    }
    return false;
}

template <typename T>
bool Heap<T>::deleteMin() {
    return(delete_index(min_index()));
}

template <typename T>
bool Heap<T>::deleteMax() {
    return(delete_index(0));
}

template <typename T>
T Heap<T>::peekMin() const {
    if(!isEmpty()) return arr[min_index()];
    else throw(std::runtime_error("Peeked an empty heap."));
}

template <typename T>
T Heap<T>::peekMax() const {
    if(!isEmpty()) return arr[0];
    else throw(std::runtime_error("Peeked an empty heap."));
}

int power(int b, int e) {
    int p = 1;
    for(int i = 0; i < e; i++) {
        p *= b;
    }
    return p;
}

template class Heap<Game>;
template int Heap<Game>::foldLevelsHelp(int, LevelType, int (*)(const Game&, int), int) const;
template int Heap<Game>::foldLevels(LevelType, int (*)(const Game&, int), int) const;
