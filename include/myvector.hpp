#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <vector>
#include <string>

typedef double coord;

class myvector {
    const std::vector<coord> values;
    const std::string id;
  public:
    myvector();
    myvector(std::vector<coord> v, std::string id);
    ~myvector();
    void print();
};

#endif
