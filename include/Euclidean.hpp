#ifndef EUCLIDEAN_HPP
#define EUCLIDEAN_HPP

#include <vector>

#include "Metric.hpp"
#include "myvector.hpp"

class Euclidean: public Metric{
    int dimension;
    int tablesize;
    std::vector<std::vector<float>> vectors; //K random vectors
    std::vector<float> t; //K single precision random reals
    static int w;
    static std::vector<int> r; //K random integers<=32bit
    static unsigned int M;
  public:
    Euclidean(int dim, int tsize);
    ~Euclidean();
    void SetRandVectors();
    void SetRandR();
    void SetRandT();
    int Hash(myvector& p);
    long int get_h(int i, myvector& p);
};
#endif
