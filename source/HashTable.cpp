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

HashTable::~HashTable(){
  delete metric;
}

void HashTable::Insert(myvector& p){
  int h = metric->Hash(p);
  cout << h << endl;
  buckets[h].Insert(p);
}

void HashTable::InsertList(list<myvector>& vlist){
  for(list<myvector>::iterator it=vlist.begin(); it != vlist.end(); it++){
    Insert(*it);
  }
}
