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
#include "../include/Triangle.h"
#include "../include/Tetrahedron.h"
#include "../include/Diamond.h"

using namespace std;

map<int,int> step_4(vector<Tetrahedron> &tetra_list,vector<Diamond> &diamond_list,int [],
int [],bool [],int);
#endif




