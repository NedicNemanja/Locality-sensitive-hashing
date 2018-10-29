#include <iostream>
#include <fstream>

#include "ReadInput.hpp"
#include "myvector.hpp"
#include "HashTable.hpp"
#include "utility.hpp"
#include "ErrorCodes.hpp"
#include "LSH.hpp"

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
  cout << "Read input set of " << vectors.size() << "vectors" << endl;
  data.close();
  //Initialize Hashtables
  HashTable HTable(vectors,metric,dimension);
  //open outfile
  if(CmdArgs::OutFile.empty()){
    cout << endl << "Provide outfile path:" << endl;
    cin >> CmdArgs::OutFile;
  }
  ofstream outfile = OpenOutFile(CmdArgs::OutFile);
  /****************LSH****************************************************/
  do{
    //open and read query file
    if(CmdArgs::QueryFile.empty()){
      cout << "Provide queryfile path:" << endl;
      cin >> CmdArgs::QueryFile;
    }
    ifstream queryfile = OpenInFile(CmdArgs::QueryFile);
    double radius = FindRadius(queryfile);
    list<myvector> query_set = ReadDataset(queryfile,dimension);
    cout << "Read query set of " << query_set.size() << "vectors"<< endl;
    //NN + Range Search for every vector in query_set, write output to outfile
    Search(vectors,HTable,radius,query_set,outfile);
    //cleanup
    queryfile.close();
    //Repeat?
    cout << endl << "Repeat LHS? (y/n)" << endl;
    string answer;
    cin >> answer;
    if(answer == "y" || answer == "yes")
      CmdArgs::QueryFile.erase();
    else
      break;
  }while(1);

  outfile.close();
  return OK;
}
