#include "Euclidean.hpp"
#include "ReadInput.hpp"

#include <random>
#include <utility>  //move

using namespace std;

int Euclidean::w=4;

Euclidean::Euclidean(int dim, int tsize)
:Metric("euclidean"), dimension(dim), tablesize(tsize){
  this->SetRandVectors();

}

Euclidean::~Euclidean(){
  cout << "delete euclidean" << endl;
}

extern int CmdArgs::K;

/*Create k vectors whoose coords are independently distributed
normal distribution with mean=0 and standard deviation=1*/
void Euclidean::SetRandVectors(){
  default_random_engine generator;
  normal_distribution<float> distribution(0,1);

  for(int i=0; i<CmdArgs::K; i++){  //k vectors
    vector<float> v;
    for(int j=0; j<dimension; j++){
      v.push_back(distribution(generator));
      cout << distribution(generator) << endl;
    }
    vectors.push_back(move(v));
  }
}
