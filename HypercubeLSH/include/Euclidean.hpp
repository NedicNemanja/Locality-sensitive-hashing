#ifndef EUCLIDEAN_HPP
#define EUCLIDEAN_HPP

#include <vector>

#include "myvector.hpp"
#include "Metric.hpp"

class Euclidean: public Metric{
    int dimension;
    std::vector<std::vector<float>> vectors; //K random vectors
    std::vector<float> t; //K single precision random reals
    static int w;
  public:
    Euclidean(int dim, int tsize);
    ~Euclidean();
    void SetRandVectors();
    void SetRandT();
    unsigned int Hash(myvector& p);
    long int get_h(int i, myvector& p);
    std::vector<long int> get_g(myvector &p);
    int dim();
    //euclidean vector distance
    double vectorDistance(std::vector<coord>::iterator first,
                          std::vector<coord>::iterator last,
                          std::vector<coord>::iterator first2);
};
#endif
