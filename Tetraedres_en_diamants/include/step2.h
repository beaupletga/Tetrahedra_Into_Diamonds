#ifndef STEP2_H
#define STEP2_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <tuple>
#include <map>
#include <math.h>       /* atan */

#include "../include/Vertex.h"
#include "../include/Tetrahedron.h"
#include "../include/Diamond.h"
#include "../include/step1.h"

using namespace std;

vector<Diamond> step_2(map<tuple<int,int>,vector<Tetrahedron*>>& edge_to_tetra,vector<Tetrahedron>& tetra_list,
map<tuple<int,int>,vector<Tetrahedron*>>& edge_dict,map<tuple<int,int,int>,vector<Tetrahedron*>>& face_dict,
vector<Vertex> &vertex_list);
#endif




