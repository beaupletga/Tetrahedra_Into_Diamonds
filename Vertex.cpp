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

bool Vertex::operator==(Vertex a)
{
    return (this->id==a.id);
}