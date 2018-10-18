#ifndef BUCKET_HPP
#define BUCKET_HPP

#include "myvector.hpp"
#include <list>

class Bucket
{
    std::vector<myvector> vectors;
  public:
    Bucket();
    ~Bucket();
    void Insert(myvector& v);
    void print();
};

#endif
