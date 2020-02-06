#ifndef HASH_TABLE_INTERFACE_H
#define HASH_TABLE_INTERFACE_H

template <typename K, typename T>
class HashTableInterface {
    public:
        virtual ~HashTableInterface(){}

        virtual bool containsObj(const T& val) const = 0;

        virtual bool insert(const T& val) = 0;

        virtual bool remove(const T& val) = 0;

        virtual int numBuckets() const = 0;

        virtual int numElements() const = 0;
};

#endif