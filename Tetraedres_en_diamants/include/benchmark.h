#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <tuple>
#include <map>
#include <math.h>       /* atan */
#include <queue>
#include <stack>
#include <cassert>
#include <unordered_set>
#include <chrono> 

#include "../include/Vertex.h"
#include "../include/Triangle.h"
#include "../include/Tetrahedron.h"
#include "../include/Diamond.h"
#include "../include/navigate.h"
#include "../include/visualization.h"

using namespace std;
void time_to_access_ith_diamond(bool diamond_extra_bytes_array[],int array_size,int diamond_number);
void time_to_access_ith_tetra(bool diamond_extra_bytes_array[],int array_size,int tetra_number);
void time_to_compute_vertex_degree(int diamond_array[],bool diamond_extra_bytes_array[],int array_size,vector<tuple<int,int,int>> &permutation_array,vector<tuple<int,int,int>> &face_array,int vertex_number);
void time_to_compute_BFS(int diamond_array[],bool diamond_extra_bytes_array[],int array_size,vector<tuple<int,int,int>> &permutation_array,vector<tuple<int,int,int>> &face_array,vector<Tetrahedron> &tetra_list,int vertex_number);

void time_to_compute_vertex_degree_full_structure(vector<Diamond> &diamond_list,int vertex_number);
void time_to_compute_BFS_full_structure(vector<Diamond> &diamond_list,int diamond_number);


#endif