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
#include "../include/Tetrahedron.h"
#include "../include/Diamond.h"


using namespace std;
int ith_diamond(bool diamond_extra_bytes_array[],int array_size,int i);
int ith_tetra(bool diamond_extra_bytes_array[],int array_size,int i);
vector<int> BFS(int diamond_array[],bool diamond_extra_bytes_array[],int array_size,int starting_diamond_index);
int vertex_degree_with_minimal_array(int (diamond_array)[],bool (diamond_extra_bytes_array)[],int diamond_array_size,
vector<tuple<int,int,int>> &permutation_array,vector<tuple<int,int,int>> &face_array,int id);
void display_face_diamond(bool diamond_extra_bytes_array[],vector<tuple<int,int,int>>& face_array,int id);
int diamond_size(bool diamond_extra_bytes_array[],int array_size,int index);
vector<int> BFS_full_structure(vector<Diamond> &diamond_list,int starting_diamond_index);
unordered_set<int> vertex_degree_full_structure(vector<Diamond> &diamond_list,int id);
#endif




