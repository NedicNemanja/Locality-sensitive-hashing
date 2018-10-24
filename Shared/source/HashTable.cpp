#include "HashTable.hpp"
#include "utility.hpp"
#include "Euclidean.hpp"
#include "CosineSimilarity.hpp"
#include "ErrorCodes.hpp"
#include "ReadInput.hpp"  //cmdargs

#include <cmath> //pow()

using namespace std;

using CmdArgs::K;

/*num_of_vectors/div_tablesize is the tablesize if metric=euclidean.
Suggested: =2,=4,=8,=16 */
int div_tablesize = 4;

unsigned int TableSize(string metric, int num_vectors){
  if(metric == "euclidean")
    return num_vectors / div_tablesize;
  else if(metric == "cosine")
    return pow(2,CmdArgs::K);
  else
    exit(UNKNOWN_METRIC);
}

/*Use this constructor if you did not know the num of vectors and you stored
them temporarily in a list. This will insert all vectors from the list.*/
HashTable::HashTable(list<myvector>& vlist, string metric_name,int dimension)
:buckets(TableSize(metric_name,vlist.size()))
{
  if(metric_name == "euclidean"){
    metric = new Euclidean(dimension, buckets.size());
  }
  else if("cosine"){
    metric = new CosineSimilarity(dimension);
  }
  else{
    cout << "Unknown metric: " << metric_name << endl;
    exit(UNKNOWN_METRIC);
  }
  cout << "Creating HashTable with " << buckets.size() << "buckets"<< endl;
  InsertList(vlist);
}

/*Use this constructor if you know the size (num of vectors) for your HashTable
before you create a temporary list to store the vectors.
That way you can immediately HashTable::Insert them here*/
HashTable::HashTable(int size, string metric_name, int dimension)
:buckets(TableSize(metric_name,size))
{
  if(metric_name == "euclidean"){
    metric = new Euclidean(dimension, buckets.size());
  }
  else if("cosine"){
    metric = new CosineSimilarity(dimension);
  }
  else{
    cout << "Unknown metric: " << metric_name << endl;
    exit(UNKNOWN_METRIC);
  }
  cout << "Creating HashTable with " << buckets.size() << "buckets"<< endl;
}

/*Copy constructor. Creates a new metric. But the buckets are copied.*/
HashTable::HashTable(const HashTable &obj)
:buckets(obj.buckets)
{
    if(obj.metric->name == "euclidean"){
      metric = new Euclidean(obj.metric->dim(), buckets.size());
    }
    else if(obj.metric->name == "cosine"){
      metric = new CosineSimilarity(obj.metric->dim());
    }
    else{
      cout << "Unknown metric: " << obj.metric->name << endl;
      exit(UNKNOWN_METRIC);
    }
  cout << "Creating HashTable by copy with " << buckets.size()<<"buckets"<<endl;
}

HashTable::~HashTable(){
  cout << "HashTable destroyed" << endl;
  delete metric;
}

/*Insert a new vector to the table*/
void HashTable::Insert(myvector& p){
  unsigned int h = metric->Hash(p);
  //scout << h << " ";
  buckets[h].push_back(p);
}

/*Insert all elements of a list to hashtable*/
void HashTable::InsertList(list<myvector>& vlist){
  for(list<myvector>::iterator it=vlist.begin(); it != vlist.end(); it++){
    Insert(*it);
  }
}

/*Find in which bucket a vector should belong.*/
Bucket HashTable::get_bucket(myvector& v){
  return buckets[metric->Hash(v)];
}


//Print bucket sizes
void HashTable::PrintBuckets(){
  cout << "Printing buckets" << endl;
  for(int i=0; i<buckets.size(); i++){
    cout << "bucket" << i << ":" << buckets[i].size() << endl;
  }
}
