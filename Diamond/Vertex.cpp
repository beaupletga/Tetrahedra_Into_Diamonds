#include "Vertex.h"
#include <cmath>
#include <iostream>
using namespace std;

Vertex::Vertex(int id,vector<double> coords)
{
    this->id=id;
    this->coords=coords;
}

int Vertex::get_id()
{
    return this->id;
}

vector<Vertex *> Vertex::get_neighbours()
{
    return this->neighbours;
}

void Vertex::add_neighbours(vector<Vertex *> neighbours)
{
    for (int i=0;i<neighbours.size();i++)
    {
        bool already_in=false;
        for (int j=0;j<this->neighbours.size();j++)
        {
            if (neighbours[i]->get_id()==this->neighbours[j]->get_id())
            {
                already_in=true;
                break;
            }
        }
        if (!already_in && this->id!=neighbours[i]->get_id())
        {
            this->neighbours.push_back(neighbours[i]);
        }
    }
}

bool Vertex::operator==(Vertex a)
{
    return (this->id==a.id);
}