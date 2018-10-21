#ifndef NN_HPP
#define NN_HPP

#include <list>
#include <vector>
#include <fstream>

#include "HashTable.hpp"
#include "myvector.hpp"

void Search(std::list<myvector> &vlist, std::vector<HashTable*> &Hashtables,
            double radius, std::list<myvector> &queries,std::ofstream &outfile);

myvector NearestNeighbor( std::vector<HashTable*> &Hashtables, myvector &q,
                          double* distanceLHS, double* timeLHS);

std::list<myvector> RangeSearch(std::vector<HashTable*> &Hashtables,myvector &q,
                                double radius);
#endif
