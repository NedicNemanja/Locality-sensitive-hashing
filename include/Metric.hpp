#ifndef METRIC_HPP
#define METRIC_HPP

#include <string>
#include "myvector.hpp"

class Metric {
    std::string name;
  public:
    Metric(std::string);
    virtual ~Metric();
    virtual int Hash(myvector& p)=0;
};

#endif
