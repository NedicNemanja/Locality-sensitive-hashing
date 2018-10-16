#ifndef READINPUT_HPP
#define READINPUT_HPP

#include <iostream>
#include <fstream>

#include "myvector.hpp"

namespace CmdArgs{
    extern std::string InputFile;
    extern std::string QueryFile;
    extern std::string OutFile;
    extern int K,L;
}

/*Parse cmd line arguments and read from cin any that are missing*/
void ParseArguments(int argc, char** argv);


void ReadDataset(std::string inputfile);

//Check the first vector and find its dimension
int FindDimension(std::ifstream &data);

//read coordinates of a myvector and return true for success, else false
bool GetVectorCoords(std::ifstream &data,std::vector<coord> &coords);

#endif
