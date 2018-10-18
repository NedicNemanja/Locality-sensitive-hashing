#ifndef EUCLIDEAN_HPP
#define EUCLIDEAN_HPP

#include <vector>

#include "Metric.hpp"
#include "myvector.hpp"

class Euclidean: public Metric{
    int dimension;
    int tablesize;
    std::vector<std::vector<float>> vectors; //random vectors
    static std::vector<int> r; //random int<=32bit
    float t; //single precision?
    static int w;
  public:
    Euclidean(int dim, int tsize);
    ~Euclidean();
    void SetRandVectors();
    //SetRandR();
    //Hash(myvector p);
};

#endif
