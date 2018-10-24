#ifndef EUCLIDEAN_HPP
#define EUCLIDEAN_HPP

#include <vector>

#include "myvector.hpp"
#include "Metric.hpp"

class Euclidean: public Metric{
    int dimension;
    int tablesize;
    std::vector<std::vector<float>> vectors; //K random vectors
    std::vector<float> t; //K single precision random reals
    static int w;
    static long int M;
  public:
    Euclidean(int dim, int tsize);
    ~Euclidean();
    void SetRandVectors();
    void SetRandT();
    unsigned int Hash(myvector& p);
    long int get_h(int i, myvector& p);
    int dim();
};
#endif
