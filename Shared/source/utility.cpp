#include "utility.hpp"
#include "ErrorCodes.hpp"

#include <float.h> //DBL_MAX
#include <time.h>
#include <cmath>

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
