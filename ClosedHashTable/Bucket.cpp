#include "./Bucket.h"

template <typename T>
Bucket<T>::Bucket() {
    empty = true;
}

template <typename T>
Bucket<T>::Bucket(const T& obj) {
    empty = false;
    item = obj;
}

template <typename T>
Bucket<T>::Bucket(const Bucket<T>& other) {
    empty = other.empty;
    if(!empty) item = other.item;
}

template <typename T>
Bucket<T>::~Bucket() {}

template <typename T>
bool Bucket<T>::isEmpty() const {
    return empty;
}

template <typename T>
T Bucket<T>::getItem() const {
    return item;
}

template <typename T>
bool Bucket<T>::removeItem() {
    if(empty) return false;
    else {
        empty = true;
        return true;
    }
}

template <typename T>
bool Bucket<T>::setItem(const T& obj) {
    if(empty) {
        item = obj;
        empty = false;
        return true;
    }
    return false;
}

template <typename T>
bool Bucket<T>::containsItem(const T& obj) const {
    return (!empty && (item == obj));
}

template <typename T>
Bucket<T>& Bucket<T>::operator=(const Bucket<T>& other) {
    empty = other.empty;
    if(!empty) item = other.item;
    return *this;
}