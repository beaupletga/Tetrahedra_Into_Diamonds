#include "Diamond.h"


Diamond::Diamond(vector<Tetrahedron*>& elements)
{
    this->tetra_list=elements;

}


int Diamond::get_id()
{
    return this->id;
}

vector<Tetrahedron*> Diamond::get_tetra_list()
{
    return this->tetra_list;
}

tuple<int,int> Diamond::get_central_edge()
{
    return this->central_edge;
}

vector<Vertex*> Diamond::get_vertices()
{
    return this->vertices;
}