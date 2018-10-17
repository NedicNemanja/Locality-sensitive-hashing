#ifndef BUCKET_HPP
#define BUCKET_HPP

#include "myvector.hpp"
#include <list>

class Bucket
{
    std::list<myvector> vectors;
  public:
    Bucket();
    ~Bucket();
    //Insert(myvector v);
};

#endif
