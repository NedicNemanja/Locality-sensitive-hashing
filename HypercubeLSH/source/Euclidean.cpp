#include "Euclidean.hpp"
#include "ReadInput.hpp"
#include "utility.hpp"

#include <random>
#include <utility>  //move
#include <limits>
#include <cstdint>
#include <numeric>  //inner_product

using namespace std;

int Euclidean::w=4;
unsigned int Euclidean::M = UINT32_MAX-4;   //4294967291 is prime
std::vector<int> Euclidean::r;

Euclidean::Euclidean(int dim, int tsize)
:Metric("euclidean"), dimension(dim), tablesize(tsize){
  this->SetRandVectors();
  if(r.empty())
    this->SetRandR();
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

void Euclidean::SetRandR(){
  random_device generator;
  uniform_int_distribution<int> distribution(INT32_MIN,INT32_MAX);

  for(int i=0; i<CmdArgs::K; i++){
    r.push_back(distribution(generator));
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

unsigned int Euclidean::Hash(myvector &p){
  unsigned int result=0;
  for(int i=0; i<CmdArgs::K; i++){  //overflow danger in case 2^k>uint size
    result <<= 1;         ///shift to make room for new lsb
    result += MOD(get_h(i,p),2); //add 1 or 0
  }
  return result;
}

long int Euclidean::get_h(int i, myvector& p){
  double pv_inner = inner_product(p.begin(), p.end(), vectors[i].begin(), 0);
/*  cout << "inner_product of ";
  p.print();
  cout << endl << " and " << endl;
  printVector(vectors[i]);
  cout << "=" << pv_inner << endl;
  cout << "(" << pv_inner << "+" << t[i] << ")/" << w << "=" << floor( (pv_inner +t[i]) / w) << endl;
*/  return floor( (pv_inner +t[i]) / w);
}

int Euclidean::dim(){
  return dimension;
}