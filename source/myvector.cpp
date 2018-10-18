#include "myvector.hpp"

#include <iostream>

myvector::myvector(){}

myvector::myvector(const myvector& obj)
:values(obj.values),id(obj.id){}

myvector::myvector(std::vector<coord> v, std::string id)
:values(v), id(id) {}

myvector::~myvector(){}

void myvector::print(){
  for(size_t i=0; i<this->values.size(); i++){
    std::cout << this->values.at(i) << " ";
  }
  //std::cout << std::endl << "-------------------" <<  std::endl;
}

int myvector::size(){ return values.size(); }
std::vector<coord>::iterator myvector::begin(){ return values.begin(); }
std::vector<coord>::iterator myvector::end(){ return values.end(); }
