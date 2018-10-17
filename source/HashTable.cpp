#include "HashTable.hpp"
#include "utility.hpp"

using namespace std;

HashTable::HashTable(list<myvector> vlist)
:buckets((int)(vlist.size()/4))
{
}

HashTable::~HashTable(){}
