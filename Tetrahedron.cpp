#include "Tetrahedron.h"

using namespace std;

Tetrahedron::Tetrahedron(int id,vector<Vertex> vertex_list)
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

void Tetrahedron::display_vertices_id()
{
    for(Vertex i : this->vertices)
    {
        cout<<i.get_id()<<" ";
    }
    cout<<endl;
}

vector<Tetrahedron> Tetrahedron::get_neighbours()
{
    return this->neighbours;
}

int Tetrahedron::get_id()
{
    return this->id;
}

vector<Vertex> Tetrahedron::get_vertices()
{
    return this->vertices;
}

bool Tetrahedron::is_adjacent(Tetrahedron tetra)
{
    int count=0;
    for(int i=0;i<this->vertices.size();i++)
    {
        for(int j=0;j<tetra.get_vertices().size();j++)
        {
            if (this->vertices[i]==tetra.get_vertices()[j])
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
