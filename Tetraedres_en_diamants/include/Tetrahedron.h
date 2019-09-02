#ifndef TETRAHEDRON_H
#define TETRAHEDRON_H

#include <iostream>
#include <algorithm>
#include <tuple>
#include <map>
#include <assert.h>

#include "../include/Vertex.h"
// #include "Diamond.h"
using namespace std;

// forward declaration of the class diamond because of cyclic declaration
class Diamond;

class Tetrahedron
{
    public:
        Tetrahedron(int,vector<Vertex *>);
        // bool is_adjacent(Tetrahedron);
        int get_id();
        tuple<double,double,double> get_barycenter();
        void display_vertices_id();
        void display_edges();
        vector<Vertex*> get_vertices();
        vector<Tetrahedron*> get_neighbours();
        void add_edge_vertex_match(tuple<int,int>,Vertex*);
        vector<tuple<int,int>> enumerate_edges();
        vector<tuple<int,int,int>> enumerate_faces();
        bool is_adjacent(Tetrahedron*);
        void set_in_diamond(bool);
        bool get_in_diamond();
        void set_is_on_boundary(bool);
        bool get_is_on_boundary();
        void add_neighbour(Tetrahedron*);
        Diamond* get_diamond_ref();
        int get_position_in_diamond();
        void set_diamond_ref(Diamond*);
        void set_position_in_diamond(int); 
        tuple<int,int,int> get_opposite_face(Vertex*);

        int count_matched;

    private:
        int id;
        vector<Vertex*> vertices;
        vector<Tetrahedron*> neighbours;
        vector<tuple<int,int>> edges;
        bool in_diamond;
        bool is_on_boundary;

        Diamond* diamond_ref;
        int position_in_diamond;
};


#endif