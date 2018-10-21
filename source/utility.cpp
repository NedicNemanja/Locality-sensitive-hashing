#include "utility.hpp"

#include <float.h> //DBL_MAX
#include <time.h>

using namespace std;

double ExhaustiveSearch(list<myvector> &vlist, myvector &q, double* distTrue){
  struct timespec start,end;
  clock_gettime(CLOCK_MONOTONIC,&start);

  myvector nn;
  double min_dist = DBL_MAX, timeTrue;
  for(list<myvector>::iterator it=vlist.begin(); it != vlist.end(); it++){
    double distance = vectorDistance(q.begin(),q.end(),(*it).begin());
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
