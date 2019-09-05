#ifndef SAVE_H
#define SAVE_H

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
#include "../include/Tetrahedron.h"
#include "../include/Diamond.h"
#include "../include/navigate.h"

using namespace std;

void save_full_structure_to_mesh(vector<Vertex> &vertex_list,vector<Diamond> &diamond_list, map<tuple<int,int,int>,vector<Tetrahedron*>> &face_dict);
void save_full_structure_to_off(vector<Vertex> &vertex_list,vector<Diamond> &diamond_list, map<tuple<int,int,int>,vector<Tetrahedron*>> &face_dict);


#endif