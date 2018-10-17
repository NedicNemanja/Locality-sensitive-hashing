#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <list>
#include <vector>

#include "myvector.hpp"
#include "Bucket.hpp"

/*
class AmplifiedHashFunction
{
    std::vector<Metric> functions;
  public:
    AmplifiedHashFunction();
    ~AmplifiedHashFunction();
}

class ClassicHashFunction {
    std::vector<int> r(K); //vector of random integers
    int M;  //prime M=2^32-1
  public:
    ClassicHashFunction();
    ~ClassicHashFunction();
};
*/

class HashTable
{
  //  AmplifiedHashFunction g;
  //  static ClassicHashFunction f;
    std::vector<Bucket> buckets;
  public:
    HashTable(std::list<myvector> v);
    ~HashTable();
    //Insert(myvector v);
    //InsertList(list<myvector> vectors);
};

#endif
