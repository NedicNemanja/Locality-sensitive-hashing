#include "LSH.hpp"
#include "utility.hpp"
#include "WriteOutput.hpp"
#include "Metric.hpp"
#include "ReadInput.hpp"

#include <float.h> //DBL_MAX
#include <time.h>
#include <iostream>

using namespace std;

void Search(list<myvector> &vlist, HashTable &HTable,
            double radius, list<myvector> &queries, ofstream &outfile)
{
  cout << endl << "Search start" << endl;
  double max_ratio=0,total_time=0; //max distanceLHS/distanceTrue ratio
  int progress=0;
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
    if(distanceLHS/distanceTrue > max_ratio){
      max_ratio = distanceLHS/distanceTrue;
    }
    total_time += timeLHS;
    //print progress bar to console
    if((++progress) % 10 == 0)
      printProgress((double)progress/queries.size());
  }
  cout <<endl<<endl<<"Max distanceLSH/distanceTrue ratio: "<< max_ratio << endl;
  cout << "Mean time to find NearestNeighbor LSH: " << total_time/queries.size()
       << endl;
}

myvector NearestNeighbor( HashTable &HTable, myvector &q,
                          double* distanceLHS, double* timeLHS)
{
  struct timespec start,end;
  clock_gettime(CLOCK_MONOTONIC,&start);

  myvector nn;
  double min_dist= DBL_MAX;
  int checked=0; //num of vectors checked for this q so far
  int q_hash = HTable.get_hash(q);
  Bucket bucket = HTable.get_bucket_at(q_hash); //find corresponding bucket
  Metric* metric = HTable.get_metric();

  //check each p in bucket
  for(vector<myvector>::iterator p=bucket.begin(); p != bucket.end(); p++){
    //if(checked > CmdArgs::M) break; //don't check more than M vectors in total
    double distance = metric->vectorDistance(q.begin(),q.end(),(*p).begin());
    if(distance < min_dist){
      nn = *p;
      min_dist = distance;
    }
    checked++;
  }
  int hamm_dist = 1, hamm_index=0;
  std::vector<int> HammNeighbors = HammingNeighbors(q_hash,CmdArgs::K);
  //check each p in neighboring buckets
  for(int i=1; i<CmdArgs::probes && i<pow(2,CmdArgs::K); i++){
    //if(checked > CmdArgs::M) break; //don't check more than M vectors in total
    if(hamm_index == HammNeighbors.size()){
      //if you run out of neighbors, look at Hamming Distance +1
      HammNeighbors = HammingNeighbors(q_hash, CmdArgs::K, ++hamm_dist);
      hamm_index = 0; //new vector, reset index
    }
    //next edge (bucket) with Humming Distance =1
    bucket = HTable.get_bucket_at(HammNeighbors[hamm_index++]);
    //check each p in bucket
    for(vector<myvector>::iterator p=bucket.begin(); p != bucket.end(); p++){
      //if(checked > CmdArgs::M) break; //don't check more than M vectors
      double distance = metric->vectorDistance(q.begin(),q.end(),(*p).begin());
      if(distance < min_dist){
        nn = *p;
        min_dist = distance;
      }
      checked++;
    }
  }
  clock_gettime(CLOCK_MONOTONIC,&end);
  *timeLHS = end.tv_sec-start.tv_sec + (end.tv_nsec-start.tv_nsec)/1000000000.0;
  *distanceLHS = min_dist;
  return nn;
}

list<myvector> RangeSearch(HashTable &HTable, myvector &q,double radius)
{
  int checked=0; //num of vectors checked for this q so far
  list<myvector> neighbors;
  int q_hash = HTable.get_hash(q);
  Bucket bucket = HTable.get_bucket_at(q_hash); //find corresponding bucket
  Metric* metric = HTable.get_metric();

  //check each p in bucket
  for(vector<myvector>::iterator p=bucket.begin(); p != bucket.end(); p++){
    //if(checked > CmdArgs::M) break; //don't check more than M vectors in total
    double distance = metric->vectorDistance(q.begin(),q.end(),(*p).begin());
    if( distance < radius){
      neighbors.push_back(*p);
    }
    checked++;
  }
  int hamm_dist = 1, hamm_index=0;
  std::vector<int> HammNeighbors = HammingNeighbors(q_hash,CmdArgs::K);
  //check each p in neighboring buckets
  for(int i=0; i<CmdArgs::probes-1; i++){
    //if(checked > CmdArgs::M) break; //don't check more than M vectors in total
    if(hamm_index == HammNeighbors.size()){
      //if you run out of neighbors, look at Hamming Distance +1
      HammNeighbors = HammingNeighbors(q_hash, CmdArgs::K, ++hamm_dist);
      hamm_index = 0; //new vector, reset index
    }
    //next edge (bucket) with Humming Distance =1
    bucket = HTable.get_bucket_at(HammNeighbors[hamm_index]);
    //check each p in bucket
    for(vector<myvector>::iterator p=bucket.begin(); p != bucket.end(); p++){
      //if(checked > CmdArgs::M) break; //don't check more than M vectors in total
      double distance = metric->vectorDistance(q.begin(),q.end(),(*p).begin());
      if( distance < radius){
        neighbors.push_back(*p);
      }
      checked++;
    }
  }
  return neighbors;
}
