#ifndef STEP1_H
#define STEP1_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <tuple>
#include <map>
#include <math.h>       /* atan */
#include <queue>
#include <stack>
#include <cassert>
#include <unordered_set>

#include "../include/Vertex.h"
#include "../include/Triangle.h"
#include "../include/Tetrahedron.h"
#include "../include/Diamond.h"

using namespace std;

bool is_cycle(vector<Tetrahedron*>&);
map<tuple<int,int>,vector<Tetrahedron*>> step_1_bfs(vector<Vertex>&,vector<Tetrahedron>&,map<tuple<int,int>,vector<Tetrahedron*>>&);
map<tuple<int,int>,vector<Vertex*>> step_1_vertex_choose_neighbour(vector<Vertex>&,vector<Tetrahedron>&,map<tuple<int,int>,vector<Tetrahedron*>>&);
map<tuple<int,int>,vector<Tetrahedron*>> step_1_edge_degree(vector<Vertex>&,vector<Tetrahedron>&,map<tuple<int,int>,vector<Tetrahedron*>>&);
map<tuple<int,int>,vector<Tetrahedron*>> step_1_random(vector<Vertex>&,vector<Tetrahedron>&,map<tuple<int,int>,vector<Tetrahedron*>>&,map<tuple<int,int>,vector<Tetrahedron*>>&);

#endif




