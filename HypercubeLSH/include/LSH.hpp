#ifndef NN_HPP
#define NN_HPP

#include <list>
#include <vector>
#include <fstream>

#include "HashTable.hpp"
#include "myvector.hpp"

void Search(std::list<myvector> &vlist,HashTable &HTable,
            double radius, std::list<myvector> &queries,std::ofstream &outfile);

myvector NearestNeighbor( HashTable &HTable, myvector &q,
                          double* distanceLHS, double* timeLHS);

std::list<myvector> RangeSearch(HashTable &HTable,myvector &q, double radius);

#endif
