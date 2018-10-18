#ifndef METRIC_HPP
#define METRIC_HPP

#include <string>

class Metric {
    std::string name;
  public:
    Metric(std::string);
    virtual ~Metric();
};

#endif
