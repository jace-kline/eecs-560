#include "./Utils.h"

template <typename T>
T* deepCopyArr(T* other, int size) {
    T* newArr = new T[size];
    for(int i = 0; i < size; i++) {
        newArr[i] = other[i];
    }
    return newArr;
}