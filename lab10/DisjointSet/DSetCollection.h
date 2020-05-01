#ifndef D_SET_COLLECTION_H
#define D_SET_COLLECTION_H

#include "DNode.h"

template <typename T>
class DSetCollection {
    private:
        int max_size;
        int n;
        DNode<T>** ptrs;

    protected:
        // returns nullptr on not found
        DNode<T>* nodeOfItem(const T& x);

        // return -1 on invalid x
        int rankOfSet(const T& x);

    public:
        DSetCollection<T>(int size);
        ~DSetCollection<T>();
        bool initSingleton(const T& x);
        const T& mkUnion(const T& x, const T& y); //throws invalid object back
        const T& findRepr(const T& x); //throws invalid object
        bool pathCompress(const T& x);
        bool traversePath(const T& x, void (*eff)(const T&), void (*bridge)());

};

#endif