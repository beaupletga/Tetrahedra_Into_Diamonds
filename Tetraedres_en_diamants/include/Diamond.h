#ifndef DIAMOND_H
#define DIAMOND_H

#include "../include/Tetrahedron.h"
#include "assert.h"

#include <unordered_map>
#include <unordered_set>

using namespace std;

class Diamond
{
    public:
        Diamond(int,vector<Tetrahedron*>&,Vertex*,bool has_anchor=false);
        Diamond();
        int get_id();
        vector<Tetrahedron*> get_tetra_list();
        vector<Diamond*> get_neighbours();
        Vertex* get_anchor_vertex();
        vector<tuple<int,int,int>> get_external_faces();
        void add_neighbour(tuple<int,int,int> &,Diamond*);
        int get_neighbour_index(Diamond* neighbour);
        pair<int,int> get_central_edge();
        void set_central_edge(pair<int,int>);
        void set_anchor_vertex(Vertex*);
        void display_vertices_id();
        bool has_anchor;
        vector<int> get_vertex_order();
        vector<tuple<int,int,int>> neighbours_faces;
        void set_permutation(vector<int>&,int);
        vector<int> get_permutation(int);
        vector<int> vertex_order;
        unordered_set<int> get_vertices_id();


    private:
        int id;
        Vertex* anchor_vertex;
        pair<int,int> central_edge;
        vector<Tetrahedron*> tetra_list;
        vector<Diamond*> neighbours;
        vector<vector<int>> permutation;
};


#endif