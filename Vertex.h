#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <vector>
using namespace std;

class Vertex
{
    public:
        Vertex(int,vector<double>);
        int get_id();
        bool operator==(Vertex);

    private: 
        int id;
        vector<double> coords;
        vector<Vertex> neighbours;
};

#endif