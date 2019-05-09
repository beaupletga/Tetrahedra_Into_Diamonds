#ifndef DIAMOND_H
#define DIAMOND_H

#include "Vertex.h"
#include "Tetrahedron.h"
using namespace std;

class Diamond
{
    public:
        Diamond(int,vector<Tetrahedron*>&,Vertex*);
        int get_id();
        vector<Tetrahedron*> get_tetra_list();
        tuple<int,int> get_central_edge();
        vector<Vertex*> get_vertices();
        vector<Diamond*> get_neighbours();
        vector<tuple<int,int,int>> get_external_faces();
        void add_neighbour(tuple<int,int,int> &,Diamond*);

    private:
        int id;
        Vertex* anchor_vertex;
        vector<Tetrahedron*> tetra_list;
        tuple<int,int> central_edge;
        vector<Vertex*> vertices;
        vector<Diamond*> neighbours;
};


#endif