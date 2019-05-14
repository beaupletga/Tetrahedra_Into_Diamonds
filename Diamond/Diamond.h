#ifndef DIAMOND_H
#define DIAMOND_H

#include "Tetrahedron.h"
using namespace std;

class Diamond
{
    public:
        Diamond(int,vector<Tetrahedron*>&,Vertex*);
        int get_id();
        vector<Tetrahedron*> get_tetra_list();
        vector<Diamond*> get_neighbours();
        Vertex* get_anchor_vertex();
        vector<tuple<int,int,int>> get_external_faces();
        void add_neighbour(tuple<int,int,int> &,Diamond*);

    private:
        int id;
        Vertex* anchor_vertex;
        vector<Tetrahedron*> tetra_list;
        vector<Diamond*> neighbours;
};


#endif