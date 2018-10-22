#ifndef READINPUT_HPP
#define READINPUT_HPP

#include <iostream>
#include <fstream>
#include <list>
#include <string>

#include "myvector.hpp"

namespace CmdArgs{
    extern std::string InputFile;
    extern std::string QueryFile;
    extern std::string OutFile;
    extern int K,L;
};

/*Parse cmd line arguments and read from cin any that are missing*/
void ParseArguments(int argc, char** argv);


std::list<myvector> ReadDataset(std::ifstream &data,int dim);

std::string FindMetric(std::ifstream &data);

//Check the first vector from stream and find its dimension
int FindDimension(std::ifstream &data);

double FindRadius(std::ifstream &data);

//read coordinates+id of a myvector and return true for success, else false
bool GetVector(std::ifstream &data,std::vector<coord> &coords,std::string*, int);

std::ifstream OpenInFile(std::string &filename);
std::ofstream OpenOutFile(std::string &filename);


#endif
