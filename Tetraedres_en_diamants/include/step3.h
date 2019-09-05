#ifndef STEP3_H
#define STEP3_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <tuple>
#include <map>
#include <math.h>    
#include <assert.h> 
#include <unordered_set>
#include <queue>
#include <set>

#include "Vertex.h"
#include "Tetrahedron.h"
#include "Diamond.h"

using namespace std;
void step_3_0_set_central_edge(vector<Diamond> &,map<tuple<int,int>,vector<Tetrahedron*>> &,
map<int,vector<Tetrahedron*>> &);
void step_3_1_pair_vertices_as_anchor(vector<Diamond> &,vector<Vertex> &,map<int,vector<Tetrahedron*>> &,
map<tuple<int,int>,vector<Tetrahedron*>> &);
void step_3_2_pair_unpaired_vertices(vector<Diamond> &,vector<Vertex> &,map<int,vector<Tetrahedron*>> &);
void step_3_3_connectivity(vector<Diamond> &);
map<int,Diamond*> step_3_4_anchor_dict(vector<Diamond> &);
void step_3_5_set_neighbour_permutation(vector<Diamond> &);
#endif