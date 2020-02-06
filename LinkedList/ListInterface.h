#ifndef LIST_INTERFACE_H
#define LIST_INTERFACE_H

#include <stdexcept>

template <typename T>
class ListInterface
{

     public:

     virtual ~ListInterface(){}

     virtual bool isEmpty() const = 0;

     virtual int getLength() const = 0;

     virtual bool contains(const T& entry) const = 0;

     virtual void insertFront(const T& entry) = 0;

     virtual void insertEnd(const T& entry) = 0;

     virtual void insertAt(const T& entry, int position) throw (std::runtime_error) = 0;

     virtual void remove(int position) throw (std::runtime_error) = 0;

     virtual void clear() = 0;

     virtual T getEntry(int position) const throw (std::runtime_error) = 0;

     virtual void replace(int position, T entry) throw (std::runtime_error) = 0;

     virtual void traverse(void (*eff)(const T& val)) = 0;

     template <typename R>
     R fold(R (*func)(const T& curVal, const R& accum), const R& initVal) const;

};

#endif
