#ifndef STEP3_H
#define STEP3_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <tuple>
#include <map>
#include <math.h>    
#include <assert.h>   /* atan */

#include "Vertex.h"
#include "Triangle.h"
#include "Tetrahedron.h"
#include "Diamond.h"

using namespace std;

map<int,int> step_3(vector<Tetrahedron> &tetra_list,vector<Diamond> &diamond_list,int [],
int [],bool [],int);
#endif



