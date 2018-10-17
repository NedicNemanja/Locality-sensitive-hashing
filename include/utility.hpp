#ifndef UTILITY_HPP
#define UTILITY_HPP
#include <list>

template <class T>
void PrintList(std::list<T>& myvectors){
    // allocate an iterator that points to the first
    // element in the list
    typename std::list<T>::iterator iter = myvectors.begin();
    // continue to loop through the list until the
    // iterator hits the end of the list
    while(iter != myvectors.end())
    {
        // retrieve the myvector the iterator points at
        T& s = *iter;
        s.print();
        // now move the iterator over to the next element
        // in the list
        iter++;
    }
}

#endif
