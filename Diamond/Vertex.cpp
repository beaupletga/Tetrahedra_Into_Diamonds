#include "Vertex.h"

Vertex::Vertex(int id,vector<double> coords)
{
    this->id=id;
    this->coords=coords;
}

int Vertex::get_id()
{
    return this->id;
}

vector<double> Vertex::get_coords()
{
    return this->coords;
}

vector<Vertex*> Vertex::get_neighbours()
{
    return this->neighbours;
}

void Vertex::display_neighbours()
{
    for (Vertex* i : this->neighbours)
    {
        cout<<i->id<<" ";
    }
    cout<<endl;
}

void Vertex::add_neighbours(vector<Vertex*> neighbours)
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

bool cmp_neighbours(Vertex* lhs, Vertex* rhs)
{
    return lhs->get_id()< rhs->get_id();
}

void Vertex::sort_neighbours()
{
    sort(this->neighbours.begin(),this->neighbours.end(),cmp_neighbours);
}

