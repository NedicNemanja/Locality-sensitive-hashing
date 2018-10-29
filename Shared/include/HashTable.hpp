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
    HashTable(std::list<myvector>& vlist, std::string metric_name, int dim);
    HashTable(std::list<myvector>& vlist, std::string metric,int dim,int tsize);
    HashTable(int size, std::string metric_name, int dim);
    HashTable(const HashTable &obj);
    ~HashTable();
    Bucket get_bucket(myvector& v);
    /*get bucket, but filter out the vectors with different g()'s*/
    Bucket get_bucket_filtered(myvector &q);
    /*get bucket at pos*/
    Bucket get_bucket_at(int pos);
    Metric* get_metric();
    /*Get the hash value for p*/
    int get_hash(myvector &p);
    void Insert(myvector& v);
    void InsertList(std::list<myvector>& vlist);
    void InitBuckets(int size);
    void PrintBuckets();
};

unsigned int TableSize(std::string metric, int num_vectors);

#endif
