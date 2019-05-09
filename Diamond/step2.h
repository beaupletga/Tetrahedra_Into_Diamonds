#ifndef STEP2_H
#define STEP2_H

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
#include "step1.h"

using namespace std;

vector<Diamond> step_2(map<tuple<int,int>,vector<Vertex*>>&,
vector<Tetrahedron>&,map<tuple<int,int>,vector<Tetrahedron*>>&,
map<tuple<int,int,int>,vector<Tetrahedron*>>&);
#endif




