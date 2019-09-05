#ifndef STEP4_H
#define STEP4_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <tuple>
#include <map>
#include <math.h>    
#include <assert.h>   /* atan */

#include "../include/Vertex.h"
#include "../include/Tetrahedron.h"
#include "../include/Diamond.h"

using namespace std;

map<int,int> step_4(vector<Tetrahedron>&,vector<Diamond>&,int [],
bool [],int,map<int,Diamond*>&,vector<tuple<int,int,int>>&,
vector<tuple<int,int,int>>&);
#endif




