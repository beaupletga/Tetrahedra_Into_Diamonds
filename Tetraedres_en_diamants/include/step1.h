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
#include "../include/Tetrahedron.h"
#include "../include/Diamond.h"

using namespace std;

bool is_cycle(vector<Tetrahedron*>& tetra_list);
map<tuple<int,int>,vector<Tetrahedron*>> step_1_bfs(vector<Vertex>& vertex_list,vector<Tetrahedron>& tetra_list,map<tuple<int,int>,vector<Tetrahedron*>>& edge_dict);
#endif




