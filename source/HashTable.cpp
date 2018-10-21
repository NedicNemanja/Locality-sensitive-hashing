#include "HashTable.hpp"
#include "utility.hpp"
#include "Euclidean.hpp"

using namespace std;

inline int TableSize(int listsize){
  return listsize/4;
}

HashTable::HashTable(list<myvector>& vlist, string metric_name)
:buckets(TableSize(vlist.size()),Bucket())
{
  cout << "Creating HashTable with " << buckets.size() << "buckets"<< endl;
  if(metric_name == "euclidean")
    metric = new Euclidean(vlist.front().size(), buckets.size());
//  if(metric_name == "cosine")
//    metric = new Cosine();
  InsertList(vlist);
}

HashTable::HashTable(int size, string metric_name, int dim)
:buckets(TableSize(size))
{
  cout << "Creating HashTable with " << buckets.size() << "buckets"<< endl;
  if(metric_name == "euclidean")
    metric = new Euclidean(dim, buckets.size());
//  if(metric_name == "cosine")
//    metric = new Cosine();
  //InsertList(vlist);
}

HashTable::HashTable(const HashTable &obj)
:buckets(obj.buckets)
{
  cout << "Creating HashTable by copy with " << buckets.size() << "buckets"<< endl;
  if(obj.metric->name == "euclidean")
    metric = new Euclidean(obj.metric->dim(), buckets.size());
//  if(metric_name == "cosine")
//    metric = new Cosine();
}

HashTable::~HashTable(){
  cout << "HashTable destroyed" << endl;
  delete metric;
}

void HashTable::Insert(myvector& p){
  int h = metric->Hash(p);
  //cout << h << " ";
  buckets[h].push_back(p);
}

//insert to hashtable from a list
void HashTable::InsertList(list<myvector>& vlist){
  for(list<myvector>::iterator it=vlist.begin(); it != vlist.end(); it++){
    Insert(*it);
  }
}

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
