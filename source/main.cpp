#include <iostream>
#include <fstream>

#include "ReadInput.hpp"

using namespace std;

int main(int argc, char** argv){

  ParseArguments(argc,argv);
  ReadDataset(CmdArgs::InputFile);
}
