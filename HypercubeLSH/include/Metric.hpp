#ifndef METRIC_HPP
#define METRIC_HPP

#include <string>
#include "myvector.hpp"

class Metric {
  public:
    const std::string name;
    Metric(std::string);
    virtual ~Metric();
    virtual unsigned int Hash(myvector& p)=0;
    virtual int dim()=0;
};

#endif
