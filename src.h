#ifndef SRC_H
#define SRC_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <tuple>
#include <map>


#include "Vertex.h"
#include "Triangle.h"
#include "Tetrahedron.h"
#include "src.h"

using namespace std;

vector<tuple<int,int>> enumerate_edges(vector<Vertex>);
std::map<int,vector<Tetrahedron *>> make_vertex_dict(vector<Tetrahedron>);
std::map<tuple<int,int>,vector<Tetrahedron *>> make_edge_dict(vector<Tetrahedron>);
void preprocessing_tetra(tuple<vector<vector<double>>,vector<vector<double>>>, vector<Vertex>&, vector<Tetrahedron>&);

#endif




