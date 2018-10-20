#include <iostream>
#include <fstream>

#include "ReadInput.hpp"
#include "myvector.hpp"
#include "HashTable.hpp"
#include "utility.hpp"
#include "ErrorCodes.hpp"

using namespace std;

void PrintList(list<myvector>& myvectors);

int main(int argc, char** argv){
  /*****************PREPROCESSING*************************************/
  ParseArguments(argc,argv);
  //open input file
  ifstream data = OpenInFile(CmdArgs::InputFile);
  //read data from file
  string metric = FindMetric(data);
  int dimension = FindDimension(data);
  list<myvector> vectors = ReadDataset(data,dimension);
  data.close();
  //Initialize Hashtables
  vector<HashTable*> Hashtables(CmdArgs::L);
  for(int i=0; i<CmdArgs::L; i++){
    HashTable* h = new HashTable(vectors,metric);
    Hashtables[i]=h;
    cout << endl;
  }
  //open outfile
  if(CmdArgs::OutFile.empty()){
    cout << "Provide outfile path:" << endl;
    cin >> CmdArgs::OutFile;
  }
  ofstream outfile = OpenOutFile(CmdArgs::OutFile);
  /****************LHS****************************************************/
  do{
    //open and read query file
    if(CmdArgs::QueryFile.empty()){
      cout << "Provide queryfile path:" << endl;
      cin >> CmdArgs::QueryFile;
    }
    ifstream queryfile = OpenInFile(CmdArgs::QueryFile);
    double radius = FindRadius(queryfile);
    list<myvector> query_set = ReadDataset(queryfile,dimension);
    PrintList<myvector>(query_set);
    //NearestNeighborSearch(Hashtables);

    //cleanup
    queryfile.close();
    //Repeat?
    cout << "Repeat LHS? (y/n)" << endl;
    string answer;
    cin >> answer;
    if(answer == "y" || answer == "yes")
      CmdArgs::QueryFile.erase();
    else
      break;
  }while(1);

  //cleanup
  for(int i=0; i<CmdArgs::L; i++){
    delete Hashtables[i];
  }
  outfile.close();
  return OK;
}
