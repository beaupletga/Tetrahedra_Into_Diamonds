#ifndef STATS_H
#define STATS_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <tuple>
#include <map>

#include "Vertex.h"
#include "Triangle.h"
#include "Tetrahedron.h"
#include "Diamond.h"

using namespace std;

double average_vertex_degree(std::map<int,vector<Tetrahedron*>>&);
double average_edge_degree(std::map<tuple<int,int>,vector<Tetrahedron *>>&);
double average_edges_per_vertex(vector<Vertex>&);
void stats(map<tuple<int,int>,vector<Vertex*>>& edge_to_vertex,vector<Tetrahedron>&);

#endif