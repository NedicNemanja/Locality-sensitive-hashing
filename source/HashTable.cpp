#include "HashTable.hpp"
#include "utility.hpp"
#include "Euclidean.hpp"

using namespace std;

HashTable::HashTable(list<myvector> vlist, string metric_name)
:buckets((int)(vlist.size()/4))
{
  if(metric_name == "euclidean")
    metric = new Euclidean(vlist.front().size(), vlist.size());
//  if(metric_name == "cosine")
//    metric = new Cosine();
}

HashTable::~HashTable(){
  delete metric;
}
