#ifndef UTILITY_HPP
#define UTILITY_HPP
#include <list>

#include <vector>
#include <iterator>
#include <algorithm>
#include <iostream>

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

template<typename T>
void printVector(const T& t) {
    std::copy(t.cbegin(), t.cend(), std::ostream_iterator<typename T::value_type>(std::cout, ", "));
}

template<typename T>
void printVectorInVector(const T& t) {
    std::for_each(t.cbegin(), t.cend(), printVector<typename T::value_type>);
}

#endif
