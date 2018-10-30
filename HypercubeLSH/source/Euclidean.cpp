#include "Euclidean.hpp"
#include "ReadInput.hpp"
#include "utility.hpp"

#include <random>
#include <utility>  //move
#include <limits>
#include <cstdint>
#include <numeric>  //inner_product

using namespace std;

int Euclidean::w=450;

Euclidean::Euclidean(int dim, int tsize)
:Metric("euclidean"), dimension(dim), hmap(){
  this->SetRandVectors();
  this->SetRandT();
}

Euclidean::~Euclidean(){}

extern int CmdArgs::K;

/*Create k vectors whoose coords are independently distributed
normal distribution with mean=0 and standard deviation=1*/
void Euclidean::SetRandVectors(){
  random_device generator;
  normal_distribution<float> distribution(0,1);

  for(int i=0; i<CmdArgs::K; i++){  //k vectors
    vector<float> v;
    for(int j=0; j<dimension; j++){
      v.push_back(distribution(generator));
    }
    vectors.push_back(move(v));
  }
}

void Euclidean::SetRandT(){
  random_device generator;
  uniform_int_distribution<int> distribution(0,w);
  int n;
  for(int i=0; i<CmdArgs::K; i++){
    while((n=distribution(generator)) == w);  //set [0,w) does not include w
    t.push_back(n);
  }
}

extern int asd;

/*
unsigned int Euclidean::Hash(myvector &p){
  random_device generator;
  uniform_int_distribution<int> distribution(0,1);
  unsigned int result=0;
  for(int i=0; i<CmdArgs::K; i++){  //overflow danger in case 2^k>uint size
    int hi = get_h(i,p);  //**watch out for overflow here***
    if( hmap.find(hi) == hmap.end()){ //hi not in hmap, then add it
      hmap[hi] = distribution(generator); //set a random bit for this hi in hmap
    }
    result <<= 1;         //shift to make room for new rand lsb
    result += hmap[hi]; //add 1 or 0
  }
  asd++;
  return result;
}*/

unsigned int Euclidean::Hash(myvector &p){
  unsigned int result=0;
  for(int i=0; i<CmdArgs::K; i++){  //overflow danger in case 2^k>uint size
    result <<= 1;         //shift to make room for new rand lsb
    result += MOD((long int)get_h(i,p),2);
  }
  return result;
}

int Euclidean::get_h(int i, myvector& p){
  double pv_inner = inner_product(p.begin(), p.end(), vectors[i].begin(), 0);
/*  cout << "inner_product of ";
  p.print();
  cout << endl << " and " << endl;
  printVector(vectors[i]);
  cout << "=" << pv_inner << endl;
  cout << "(" << pv_inner << "+" << t[i] << ")/" << w << "=" << floor( (pv_inner +t[i]) / w) << endl;
*/  return floor( (pv_inner +t[i]) / w);
}

std::vector<long int> Euclidean::get_g(myvector &p){
  vector<long int> g(CmdArgs::K);
  for(int i=0; i<CmdArgs::K; i++){
    g[i] = this->get_h(i,p);
  }
  return g;
}

int Euclidean::dim(){
  return dimension;
}

double Euclidean::vectorDistance(std::vector<coord>::iterator first,
                                std::vector<coord>::iterator last,
                                std::vector<coord>::iterator first2)
{
  double dist = EuclideanVectorDistance(first,last,first2);
  return dist;
}
