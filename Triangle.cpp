#include "Triangle.h"
#include <algorithm>
#include <iostream>
using namespace std;

Triangle::Triangle(int id,vector<Vertex> vertex_list)
{
    this->id=id;
    for(int i=0;i<vertex_list.size();i++)
    {
        this->vertices.push_back(vertex_list[i]);
    }
    sort( this->vertices.begin( ), this->vertices.end( ), [ ]( Vertex& lhs, Vertex& rhs )
    {
    return lhs.get_id() < rhs.get_id();
    });
}

void Triangle::display_vertices_id()
{
    for(Vertex i : this->vertices)
    {
        cout<<i.get_id()<<" ";
    }
    cout<<endl;
}

vector<Triangle> Triangle::get_neighbours()
{
    return this->neighbours;
}

int Triangle::get_id()
{
    return this->id;
}

vector<Vertex> Triangle::get_vertices()
{
    return this->vertices;
}

bool Triangle::is_adjacent(Triangle triangle)
{
    int count=0;
    for(int i=0;i<this->vertices.size();i++)
    {
        for(int j=0;j<triangle.get_vertices().size();j++)
        {
            if (this->vertices[i]==triangle.get_vertices()[j])
            {
                count++;
            }
            if (count==2)
            {
                return true;
            }
        }
    }
    return false;
}
