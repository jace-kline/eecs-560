#ifndef HASH_TABLE_INTERFACE_H
#define HASH_TABLE_INTERFACE_H

#include "./ListInterface.h"

template <typename K, typename T>
class HashTableInterface {
    public:
        virtual ~HashTableInterface(){}

        virtual bool contains(const T& val) = 0;

        virtual bool insert(const T& val) = 0;

        virtual bool remove(const T& val) = 0;

        virtual int numBuckets() = 0;

        virtual int numElements() = 0;
};

#endif