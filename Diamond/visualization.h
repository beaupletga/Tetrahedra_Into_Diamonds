#ifndef VISUALIZATION_H
#define VISUALIZATION_H

#include <iostream>
#include <fstream> 
#include <tuple>
#include <array>
#include <vector>

#include "Tetrahedron.h"

using namespace std;

void visualize(vector<Tetrahedron>&);
void visualize_diamond_isolated(vector<Vertex> &vertex_list,vector<Tetrahedron> &, map<tuple<int,int>,vector<Tetrahedron*>>&, map<tuple<int,int>,vector<Vertex*>>&);

#endif