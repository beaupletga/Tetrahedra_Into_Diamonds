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

#include "Vertex.h"
#include "Triangle.h"
#include "Tetrahedron.h"
#include "Diamond.h"

using namespace std;
void set_central_edge(vector<Diamond> &,map<tuple<int,int>,vector<Tetrahedron*>> &,
map<int,vector<Tetrahedron*>> &);
void step_3(vector<Diamond> &,vector<Vertex> &,map<int,vector<Tetrahedron*>> &);
#endif