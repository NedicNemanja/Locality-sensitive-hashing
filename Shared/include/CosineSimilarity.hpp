#ifndef COSINESIMILARITY_HPP
#define COSINESIMILARITY_HPP

#include <vector>

#include "myvector.hpp"
#include "Metric.hpp"

class CosineSimilarity: public Metric{
    int dimension;
    std::vector<std::vector<double>> r_vectors;
  public:
    CosineSimilarity(int dim);
    ~CosineSimilarity();
    void SetRandRvectors(int d);
    unsigned int Hash(myvector& p);
    int get_h(int i,myvector &p);
    int dim();
    std::vector<long int> get_g(myvector &p);
};

#endif
