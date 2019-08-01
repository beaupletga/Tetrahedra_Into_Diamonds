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
#include "../include/Triangle.h"
#include "../include/Tetrahedron.h"
#include "../include/Diamond.h"
#include "../include/step1.h"

using namespace std;

vector<Diamond> step_2(map<tuple<int,int>,vector<Tetrahedron*>>&,
vector<Tetrahedron>&,map<tuple<int,int>,vector<Tetrahedron*>>&,
map<tuple<int,int,int>,vector<Tetrahedron*>>&,vector<Vertex>&);
#endif




