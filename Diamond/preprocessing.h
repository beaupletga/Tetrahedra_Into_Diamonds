#ifndef PREPROCESSING_H
#define PREPROCESSING_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <tuple>
#include <map>
#include <math.h>       /* atan */

#include "Vertex.h"
#include "Triangle.h"
#include "Tetrahedron.h"
#include "Diamond.h"

using namespace std;

void preprocessing_tetra(tuple<vector<vector<double>>,vector<vector<double>>>&, vector<Vertex>&, vector<Tetrahedron>&);

void make_vertex_dict(vector<Tetrahedron>&,map<int,vector<Tetrahedron*>>&);
void make_edge_dict(vector<Tetrahedron>&,map<tuple<int,int>,vector<Tetrahedron*>>&);
void make_face_dict(vector<Tetrahedron>& ,map<tuple<int,int,int>,vector<Tetrahedron*>>&);

#endif




