#ifndef DIAMOND_H
#define DIAMOND_H

#include "Vertex.h"
#include "Tetrahedron.h"
using namespace std;

class Diamond
{
    public:
        Diamond(vector<Tetrahedron*>&);
        int get_id();
        vector<Tetrahedron*> get_tetra_list();
        tuple<int,int> get_central_edge();
        vector<Vertex*> get_vertices();

    private:
        int id;
        vector<Tetrahedron*> tetra_list;
        tuple<int,int> central_edge;
        vector<Vertex*> vertices;
};


#endif