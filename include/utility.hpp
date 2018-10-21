#ifndef UTILITY_HPP
#define UTILITY_HPP
#include <list>

#include <vector>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <cmath>

#include "myvector.hpp"

double ExhaustiveSearch(std::list<myvector> &vlist, myvector &q, double* dist);


/************Most of the below were found on the internet #CodeReuse***********/

template<class Iter_T, class Iter2_T>
double vectorDistance(Iter_T first, Iter_T last, Iter2_T first2) {
  double ret = 0.0;
  while (first != last) {
    double dist = (*first++) - (*first2++);
    ret += dist * dist;
  }
  return ret > 0.0 ? sqrt(ret) : 0.0;
}

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
