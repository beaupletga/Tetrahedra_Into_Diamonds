#ifndef VISUALIZATION_H
#define VISUALIZATION_H

#include <iostream>
#include <fstream> 
#include <tuple>
#include <array>
#include <vector>

#include "../include/Tetrahedron.h"
#include "../include/Diamond.h"

using namespace std;

void visualize(vector<Tetrahedron>&);
void visualize_subset_tetra(vector<Vertex>&,vector<Tetrahedron> &,vector<int> &);
void visualize_subset_diamond(vector<Vertex> &,vector<Diamond> &,vector<int> &);
void visualize_all(vector<Vertex> &,vector<Tetrahedron> &);
void visualize_diamond_isolated(vector<Vertex> &,vector<Tetrahedron> &,
map<tuple<int,int>,vector<Tetrahedron*>>&, map<tuple<int,int>,vector<Vertex*>>&);
void visualize_diamond(vector<Vertex> &,vector<Tetrahedron> &,
vector<Diamond> &,vector<int> &,map<int,int>&);
void visualize_central_edges(vector<Vertex> &,vector<Diamond> &);
#endif