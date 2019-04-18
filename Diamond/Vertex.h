#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <vector>
using namespace std;

// class Vertex
// {
//     public:
//         Vertex(int,vector<double>);
//         int get_id();
//         bool operator==(Vertex);
//         void add_neighbours(vector<Vertex>&);
//         vector<Vertex>& get_neighbours();

//     private: 
//         int id;
//         vector<double> coords;
//         vector<Vertex> neighbours;
// };

class Vertex
{
    public:
        Vertex(int,vector<double>);
        int get_id();
        bool operator==(Vertex);
        void add_neighbours(vector<Vertex*>);
        vector<Vertex *> get_neighbours();
        void display_neighbours();

    private: 
        int id;
        vector<double> coords;
        vector<Vertex*> neighbours;
};



#endif