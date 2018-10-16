#ifndef READINPUT_HPP
#define READINPUT_HPP

#include <iostream>

namespace CmdArgs{
    extern std::string InputFile;
    extern std::string QueryFile;
    extern std::string OutFile;
    extern int K,L;
}

/*Parse cmd line arguments and read from cin any that are missing*/
void ParseArguments(int argc, char** argv);


void ReadDataset();

#endif
