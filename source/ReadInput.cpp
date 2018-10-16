#include "ReadInput.hpp"
#include "ErrorCodes.hpp"

#include <stdlib.h> //atoi
#include <string.h> //strcmp
#include <iostream>

using namespace std;

namespace CmdArgs{
    std::string InputFile;
    std::string QueryFile;
    std::string OutFile;
    int K,L;
}

/*Parse cmd line arguments and read from cin any that are missing*/
void ParseArguments(int argc, char** argv){
  int arg_index=1;
  int Input_flag=0, Query_flag=0, Out_flag=0, K_flag=0, L_flag=0;

  //scan all arguements to find identifiers
  while(arg_index < argc){
    //make sure there is an argument to check
    if(argv[arg_index] == NULL)
      break;

    if(strcmp(argv[arg_index],"-d")==0 && Input_flag==0 && argv[arg_index+1]!=NULL){
      CmdArgs::InputFile.assign(argv[++arg_index]);
      Input_flag = 1;
      arg_index++;
      continue;
    }
    if(strcmp(argv[arg_index],"-q")==0 && Query_flag==0 && argv[arg_index+1]!=NULL){
      CmdArgs::QueryFile.assign(argv[++arg_index]);
      Query_flag = 1;
      arg_index++;
      continue;
    }
    if(strcmp(argv[arg_index],"-o")==0 && Out_flag==0 && argv[arg_index+1]!=NULL){
      CmdArgs::OutFile.assign(argv[++arg_index]);
      Out_flag = 1;
      arg_index++;
      continue;
    }
    if(strcmp(argv[arg_index],"-k")==0 && K_flag==0 && argv[arg_index+1]!=NULL){
      CmdArgs::K = atoi(argv[++arg_index]);
      K_flag = 1;
      arg_index++;
      continue;
    }
    if(strcmp(argv[arg_index],"-L")==0 && L_flag==0 && argv[arg_index+1]!=NULL){
      CmdArgs::L = atoi(argv[++arg_index]);
      L_flag = 1;
      arg_index++;
      continue;
    }
    fprintf(stderr, "Unknown argument: %s\n", argv[arg_index]);
    exit(UNKNOWN_CMDARGUMENT);
  }

  //check that you got all the arguements
  if(Input_flag == 0){
    cout << "Provide dataset path: ";
    cin >> CmdArgs::InputFile;
  }
  if(Query_flag == 0){
    cout << "Provide queryset path: ";
    cin >> CmdArgs::QueryFile;
  }
  if(Out_flag == 0){
    cout << "Provide outfile path: ";
    cin >> CmdArgs::OutFile;
  }
  if(K_flag == 0){
    cout << "Set K constant: ";
    cin >> CmdArgs::K;
  }
  if(L_flag == 0){
    cout << "Set L constant: ";
    cin >> CmdArgs::L;
  }
}


void ReadDataset();
