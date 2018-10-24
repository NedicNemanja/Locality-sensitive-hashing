#include "LSH.hpp"
#include "utility.hpp"
#include "WriteOutput.hpp"

#include <float.h> //DBL_MAX
#include <time.h>
#include <iostream>

using namespace std;

void Search(list<myvector> &vlist, HashTable &HTable,
            double radius, list<myvector> &queries, ofstream &outfile)
{
  cout << "Search start" << endl;
  double max_ratio=0,max_time=0; //max distanceLHS/distanceTrue ratio
  for(list<myvector>::iterator q=queries.begin(); q != queries.end(); q++){
  //for every vector q in query set
    //find neighbors in radius
    list<myvector> rNearNeighbors;
    if(radius != 0.0)
      rNearNeighbors = RangeSearch(HTable,*q,radius);
    //run NearestNeighbor and Exaustive search for the same query and compare
    double distanceLHS, distanceTrue, timeLHS, timeTrue;
    myvector nn = NearestNeighbor(HTable,*q,&distanceLHS,&timeLHS);
    timeTrue = ExhaustiveSearch(vlist,*q,&distanceTrue);
    WriteResult(outfile, rNearNeighbors, *q, nn, distanceLHS, distanceTrue,
                timeLHS, timeTrue);
    if(distanceLHS/distanceTrue > max_ratio)
      max_ratio = distanceLHS/distanceTrue;
    if(timeLHS > max_time)
      max_time = timeLHS;
  }
  cout << "Max distanceLSH/distanceTrue ratio: " << max_ratio << endl;
  cout << "Max time to find NearestNeighbor LSH: " << max_time << endl;
}

myvector NearestNeighbor( HashTable &HTable, myvector &q,
                          double* distanceLHS, double* timeLHS)
{
  struct timespec start,end;
  clock_gettime(CLOCK_MONOTONIC,&start);

  myvector nn;
  double min_dist=DBL_MAX;
  Bucket bucket = HTable.get_bucket(q); //find corresponding bucket
  for(vector<myvector>::iterator p=bucket.begin(); p != bucket.end(); p++){
  //for each p in bucket
    double distance = vectorDistance(q.begin(),q.end(),(*p).begin());
    if( distance < min_dist){
      nn = *p;
      min_dist = distance;
    }
  }
  clock_gettime(CLOCK_MONOTONIC,&end);
  *timeLHS = end.tv_sec-start.tv_sec + (end.tv_nsec-start.tv_nsec)/1000000000.0;
  *distanceLHS = min_dist;
  return nn;
}

list<myvector> RangeSearch(HashTable &HTable, myvector &q,double radius)
{
  list<myvector> neighbors;
  Bucket bucket = HTable.get_bucket(q); //find corresponding bucket
  for(vector<myvector>::iterator p=bucket.begin(); p != bucket.end(); p++){
  //for each p in bucket
    double distance = vectorDistance(q.begin(),q.end(),(*p).begin());
    if( distance < radius){
      neighbors.push_back(*p);
    }
  }
  return neighbors;
}
