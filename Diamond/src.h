#ifndef SRC_H
#define SRC_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <tuple>
#include <map>

#include "Vertex.h"
#include "Triangle.h"
#include "Tetrahedron.h"
#include "src.h"

using namespace std;

// vector<tuple<int,int>> enumerate_edges(vector<Vertex>&);
// void make_vertex_dict(vector<Tetrahedron>&,map<int,vector<Tetrahedron>> &);
// void make_edge_dict(vector<Tetrahedron>&,map<tuple<int,int>,vector<Tetrahedron>>&);
// void preprocessing_tetra(tuple<vector<vector<double>>,vector<vector<double>>>&, vector<Vertex>& , vector<Tetrahedron>& );
// double average_vertex_degree(std::map<int,vector<Tetrahedron>>&);
// double average_edge_degree(std::map<tuple<int,int>,vector<Tetrahedron>>&);
// double average_edges_per_vertex(vector<Vertex>&);
// Vertex& pick_random_edge(Vertex&);
// void step_1(vector<Vertex>&,map<tuple<int,int>,vector<Tetrahedron>>&);

vector<tuple<int,int>> enumerate_edges(vector<Vertex>&);


void make_vertex_dict(vector<Tetrahedron>&,map<int,vector<Tetrahedron*>>&);
void make_edge_dict(vector<Tetrahedron>&,map<tuple<int,int>,vector<Tetrahedron*>>&);


void preprocessing_tetra(tuple<vector<vector<double>>,vector<vector<double>>>&, vector<Vertex>&, vector<Tetrahedron>&);
double average_vertex_degree(std::map<int,vector<Tetrahedron*>>&);
double average_edge_degree(std::map<tuple<int,int>,vector<Tetrahedron*>>);
double average_edges_per_vertex(vector<Vertex>);

Vertex* pick_random_edge(Vertex&);


void step_1(vector<Vertex>&,map<tuple<int,int>,vector<Tetrahedron*>>&);


#endif




