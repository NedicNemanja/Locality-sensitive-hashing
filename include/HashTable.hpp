#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <list>
#include <vector>

#include "myvector.hpp"
#include "Bucket.hpp"
#include "Metric.hpp"

class HashTable
{
    std::vector<Bucket> buckets;
    Metric* metric;
  public:
    HashTable(std::list<myvector>& v,std::string metric_name);
    ~HashTable();
    void Insert(myvector& v);
    void InsertList(std::list<myvector>& vlist);
    void InitBuckets(int size);

};

#endif
