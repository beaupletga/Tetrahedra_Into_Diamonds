#ifndef NAVIGATE_H
#define NAVIGATE_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <tuple>
#include <map>
#include <queue>
#include <unordered_set>
#include <stack>
#include <unistd.h>


#include "../include/Vertex.h"
#include "../include/Triangle.h"
#include "../include/Tetrahedron.h"
#include "../include/Diamond.h"


using namespace std;

vector<int> BFS(int [],bool [],int,map<int,int>&);
unordered_set<int> vertex_degree(vector<Diamond> &,int );
int vertex_degree_with_minimal_array(vector<Tetrahedron> &,
vector<Diamond> &,int [],int [],bool [],int ,vector<tuple<int,int,int>>&,
vector<tuple<int,int,int>>&,int);
void display_face_diamond(bool diamond_extra_bytes_array[],vector<tuple<int,int,int>>& face_array,int id);


#endif




