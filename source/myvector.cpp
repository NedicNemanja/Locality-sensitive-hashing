#include "myvector.hpp"

#include <iostream>

myvector::myvector(std::vector<coord> v, std::string id)
:values(v), id(id) {}

myvector::~myvector(){}

void myvector::print(){
  for(size_t i=0; i<this->values.size(); i++){
    std::cout << this->values.at(i) << " ";
  }
  std::cout << std::endl;
}
