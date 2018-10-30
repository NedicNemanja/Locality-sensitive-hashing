#include "utility.hpp"
#include "ErrorCodes.hpp"

#include <float.h> //DBL_MAX
#include <time.h>
#include <cmath>
#include <algorithm>  //find

using namespace std;

double ExhaustiveSearch(list<myvector> &vlist, myvector &q, double* distTrue){
  struct timespec start,end;
  clock_gettime(CLOCK_MONOTONIC,&start);

  myvector nn;
  double min_dist = DBL_MAX, timeTrue;
  for(list<myvector>::iterator it=vlist.begin(); it != vlist.end(); it++){
    double distance = EuclideanVectorDistance(q.begin(),q.end(),(*it).begin());
    if(distance < min_dist){
      nn = *it;
      min_dist = distance;
    }
  }

  clock_gettime(CLOCK_MONOTONIC,&end);
  *distTrue = min_dist;
  timeTrue = end.tv_sec-start.tv_sec + (end.tv_nsec-start.tv_nsec)/1000000000.0;
  return timeTrue;
}


//Modulo for integers both positive and negative
unsigned int MOD(long int a , long int b){
  if(b == 0)
    exit(MOD_ZERO_EXCEPTION);
  return (a%b+b)%b;
}

//Modulo for doubles
double MOD(double a, double b){
  if(b == 0.0)
    exit(MOD_ZERO_EXCEPTION);
  return fmod((fmod(a,b)+b),b);
}

/*Get all bit strings that have a binary-hamming-distance=1 from n
(CmdArgs::K is the lenght/number of bits)*/
std::vector<int> HammingNeighbors(int n, int k, int dist){
  std::vector<int> neighbors(pow(k,dist));
  int index=0;
  if(dist == 0){
    return neighbors;
  }
  if(dist == 1){
    for(index=0; index<k; index++){
      neighbors[index] = n ^ (1 << index);
    }
    return neighbors;
  }
  else{
    /*get those at distance-1 and those at distance-2. Find every neighbor at
    distance=1 from dist1, but exclude those at dist2(cause we will have already
    checked these)*/
    std::vector<int> dist2 = HammingNeighbors(n,k,dist-2);
    std::vector<int> dist1 = HammingNeighbors(n,k,dist-1);
    for(int elem=0; elem<dist1.size(); elem++){
      for(int i=0; i<k; i++){
        int n = dist1[elem] ^ (1 << i);
        //if n not in dist2 add it to neighbors
        if(std::find(dist2.begin(), dist2.end(), n) == dist2.end())
          neighbors[index++] = n;
      }
    }
  }
}

#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60

void printProgress (double percentage)
{
    int val = (int) (percentage * 100);
    int lpad = (int) (percentage * PBWIDTH);
    int rpad = PBWIDTH - lpad;
    printf ("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
    fflush (stdout);
}
