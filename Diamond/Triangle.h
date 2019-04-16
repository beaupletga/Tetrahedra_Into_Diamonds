#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <iostream>
#include "Vertex.h"
using namespace std;

class Triangle
{
    public:
        Triangle(int,vector<Vertex>);
        bool is_adjacent(Triangle);
        int get_id();
        void display_vertices_id();
        vector<Vertex> get_vertices();
        vector<Triangle> get_neighbours();
    private:
        int id;
        vector<Vertex> vertices;
        vector<Triangle> neighbours;
};

#endif