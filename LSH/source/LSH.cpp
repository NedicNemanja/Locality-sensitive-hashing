#include "LSH.hpp"
#include "utility.hpp"
#include "WriteOutput.hpp"
#include "Metric.hpp"

#include <float.h> //DBL_MAX
#include <time.h>
#include <iostream>

using namespace std;

/*Search for NN and neighbors inside radius for every vector in queries set
by taking advantage of LSH Hashtables.
Then compare time and distance difference between NN and Exhaustive Search.
Write out the results to outfile.*/
void Search(list<myvector> &vlist, vector<HashTable*> &Hashtables,
            double radius, list<myvector> &queries, ofstream &outfile)
{
  cout << "Search start" << endl;
  double max_ratio=0,total_time=0; //max distanceLHS/distanceTrue ratio
  int progress=0;
  //for every vector q in query set
  for(list<myvector>::iterator q=queries.begin(); q != queries.end(); q++){
    //find neighbors in radius
    list<myvector> rNearNeighbors;
    if(radius != 0.0)
      rNearNeighbors = RangeSearch(Hashtables,*q,radius);
    //run NearestNeighbor and Exaustive search for the same query and compare
    double distanceLHS, distanceTrue, timeLHS, timeTrue;
    myvector nn = NearestNeighbor(Hashtables,*q,&distanceLHS,&timeLHS);
    timeTrue = ExhaustiveSearch(vlist,*q,&distanceTrue);
    WriteResult(outfile, rNearNeighbors, *q, nn, distanceLHS, distanceTrue,
                timeLHS, timeTrue);
    if(distanceLHS/distanceTrue > max_ratio)
      max_ratio = distanceLHS/distanceTrue;
    total_time += timeLHS;
    //print progress bar to console
    if((++progress) % 10 == 0)
      printProgress((double)progress/queries.size());
  }
  cout << endl << "Max distanceLSH/distanceTrue ratio: " << max_ratio << endl;
  cout << "Mean time to find NearestNeighbor LSH: " << total_time/queries.size() << endl;
}


/*In all Hashtables search for NN of q*/
myvector NearestNeighbor( vector<HashTable*> &Hashtables, myvector &q,
                          double* distanceLHS, double* timeLHS)
{
  struct timespec start,end;
  clock_gettime(CLOCK_MONOTONIC,&start);

  myvector nn;
  double min_dist=DBL_MAX;
  //for every Hashtable
  for(int i=0; i<Hashtables.size(); i++){
    //find corresponding bucket (and filter for g's in case of euclidean)
    Bucket bucket = Hashtables[i]->get_bucket_filtered(q);
    Metric* metric = Hashtables[i]->get_metric();
    //for each p in bucket
    for(Bucket::iterator p=bucket.begin(); p != bucket.end(); p++){
      double distance = metric->vectorDistance(q.begin(),q.end(),(*p).begin());
      if( distance < min_dist){
        nn = *p;
        min_dist = distance;
      }
    }
  }
  clock_gettime(CLOCK_MONOTONIC,&end);
  *timeLHS = end.tv_sec-start.tv_sec + (end.tv_nsec-start.tv_nsec)/1000000000.0;
  *distanceLHS = min_dist;
  return nn;
}


/*In all Hashtables search for vectors that are inside the radius of q*/
list<myvector> RangeSearch(vector<HashTable*> &Hashtables, myvector &q,
                          double radius)
{
  list<myvector> neighbors;
  //for every Hashtable
  for(int i=0; i<Hashtables.size(); i++){
    //find corresponding bucket (and filter for g's in case of euclidean)
    Bucket bucket = Hashtables[i]->get_bucket_filtered(q);
    Metric* metric = Hashtables[i]->get_metric();
    //for each p in bucket
    for(Bucket::iterator p=bucket.begin(); p != bucket.end(); p++){
      double distance = metric->vectorDistance(q.begin(),q.end(),(*p).begin());
      if( distance < radius){
        neighbors.push_back(*p);
      }
    }
  }
  return neighbors;
}
