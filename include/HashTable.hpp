#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <list>
#include <vector>

#include "myvector.hpp"
#include "Metric.hpp"

typedef std::vector<myvector> Bucket;

class HashTable
{
    std::vector<Bucket> buckets;
    Metric* metric;
  public:
    HashTable(std::list<myvector>& vlist, std::string metric_name);
    HashTable(int size, std::string metric_name, int dim);
    HashTable(const HashTable &obj);
    ~HashTable();
    void Insert(myvector& v);
    void InsertList(std::list<myvector>& vlist);
    void InitBuckets(int size);
    void PrintBuckets();
    Bucket get_bucket(myvector& v);
};

#endif
