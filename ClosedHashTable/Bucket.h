#ifndef BUCKET_H
#define BUCKET_H

template <typename T>
class Bucket {
    private:
        bool empty; // Has never been filled or has been deleted
        T item;
    public:
        Bucket<T>();
        Bucket<T>(const T& obj);
        Bucket<T>(const Bucket<T>& other);
        ~Bucket<T>();
        bool isEmpty() const;
        T getItem() const;

        // Returns true if the bucket was not empty initially
        // and the empty flag was changed from true to false
        bool removeItem();

        // Returns true if the bucket was empty and therefore
        // the object could be placed there, otherwise false.
        // This is because we never want to overwrite a position
        // in a hash table
        bool setItem(const T& obj);

        bool containsItem(const T& obj) const;
        Bucket<T>& operator=(const Bucket<T>& other);
};

#endif