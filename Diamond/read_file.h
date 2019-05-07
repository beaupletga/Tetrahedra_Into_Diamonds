#ifndef READ_FILE_H
#define READ_FILE_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <tuple>
#include <tuple>
#include "Vertex.h"


using namespace std;

vector<double> split(string,int,bool);
tuple<vector<vector<double>>,vector<vector<double>>> read_tet_file(string);
tuple<vector<vector<double>>,vector<vector<double>>> read_mesh_file(string);


#endif




