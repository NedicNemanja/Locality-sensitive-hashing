#include <iostream>
#include <fstream>

#include "ReadInput.hpp"
#include "myvector.hpp"
#include "HashTable.hpp"
#include "utility.hpp"

using namespace std;

void PrintList(list<myvector>& myvectors);

int main(int argc, char** argv){

  ParseArguments(argc,argv);
  list<myvector> vectors = ReadDataset(CmdArgs::InputFile);
  HashTable H(vectors);
}
