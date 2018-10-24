#include "ReadInput.hpp"
#include "ErrorCodes.hpp"
#include "myvector.hpp"

#include <stdlib.h> //atoi
#include <string.h> //strcmp
#include <sstream>
#include <utility>  //std::move()

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
  if(K_flag == 0){
    cout << "k = 4 (Default. Use -k to set.)" << endl;
    CmdArgs::K = 4;
  }
  if(L_flag == 0){
    cout << "L = 5 (Default. Use -L to set.)" << endl;
    CmdArgs::L = 5;
  }
}


list<myvector> ReadDataset(ifstream &data, int dim){
  //read coords from input and initialize vectors
  string id;
  vector<coord> coords(dim);  //temp vector that gets overwritten every loop
  list<myvector> vectors;
  while(GetVector(data, coords, &id, dim)){
      myvector vec(coords,id); //try move(coords) here!!!!!
      vectors.push_back(vec);
  }
  return vectors;
}

//read coordinates of a vector and return true for success, else false
bool GetVector(ifstream &data,vector<coord> &coords, string* id, int dim){
  //read id
  data >> *id;
  if(data.eof()) return false;
  //read coords
  for(int i=0; i<dim; i++){
    data >> coords.at(i);
    if(data.eof()) return false;
  }
  return true;
}

//check for @metric definition in the 1st line of the file
string FindMetric(ifstream &data){
  string metric;
  char c;
  data >> c;
  if(c == '@'){ //metric defined
    data >> metric;
    string str;
    getline(data,str);  //read till carriage return
  }
  else{         //undefined, proceed with default: euclidean
    metric.assign("euclidean");
    data.putback(c);
    if(!data.good())
      exit(BAD_STREAM);
  }
  cout << "Metric: " << metric << endl;
  return metric;
}


//Check the first vector and find its dimension
int FindDimension(ifstream &data){
  int dimension=0;
  streampos oldpos = data.tellg();  // stores the stream position
  string line;
  getline(data,line);               //get the whole vector
  istringstream is(line);         //treat line like a stream
  string id;                      //skip first string, that's the id
  is >> id;
  coord n;
  while( is >> n ) {                //count coords in line
    dimension++;
  }
  data.seekg (oldpos);   // get back to the position
  return dimension;
}

double FindRadius(ifstream &data){
  streampos oldpos = data.tellg();  // stores the stream position
  double radius = 0;
  string str;
  data >> str;
  if(str == "Radius:"){ //radius defined in file
    data >> radius;
    string str;
    getline(data,str);  //read till carriage return
    cout << "Radius: " << radius << endl;
  }
  else{         //undefined, the radius search will not be done
    data.seekg (oldpos);   // get back to the starting position
    cout << "Radius: 0. Skipping radius search." << endl;
  }
  return radius;
}

ifstream OpenInFile(string &filename){
  ifstream file(filename);
  if(!file.is_open()){
    cerr << "Couldn't open " << filename << endl;
    exit(FILE_ACCESS);
  }
  return file;
}

ofstream OpenOutFile(string &filename){
  ofstream file(filename);
  if(!file.is_open()){
    cerr << "Couldn't open " << filename << endl;
    exit(FILE_ACCESS);
  }
  return file;
}
