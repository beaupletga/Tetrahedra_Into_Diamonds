#ifndef TETRAHEDRON_H
#define TETRAHEDRON_H

#include <iostream>
#include <algorithm>
#include "Vertex.h"
using namespace std;

class Tetrahedron
{
    public:
        Tetrahedron(int,vector<Vertex *>);
        bool is_adjacent(Tetrahedron);
        int get_id();
        void display_vertices_id();
        vector<Vertex> get_vertices();
        vector<Tetrahedron> get_neighbours();
    private:
        int id;
        vector<Vertex> vertices;
        vector<Tetrahedron> neighbours;
};

#endif