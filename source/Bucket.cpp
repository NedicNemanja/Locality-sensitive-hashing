#include "Bucket.hpp"

using namespace std;

#include <iostream>

Bucket::Bucket(){}

Bucket::~Bucket(){}

void Bucket::Insert(myvector& p){
  vectors.push_back(p);
}