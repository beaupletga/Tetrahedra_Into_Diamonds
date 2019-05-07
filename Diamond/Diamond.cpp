#include "Diamond.h"

// constructor for each diamond
// we know that the set of tetra shape as a cycle
Diamond::Diamond(int id,vector<Tetrahedron*>& elements)
{
    this->id=id;
    bool already_in=false;
    this->tetra_list.push_back(elements[0]);
    // we want to add the tetra such that the order is the same as in the cycle around the central edge
    while (this->tetra_list.size()!=elements.size())
    {
        for(int i=0;i<elements.size();i++)
        {
            already_in=false;
            // if the new element is adjacent to the last added one
            if (elements[i]->is_adjacent(this->tetra_list.back()))
            {
                // we check that this new element isn't already added
                for (int j=0;j<this->tetra_list.size();j++)
                {
                    if (this->tetra_list[j]->get_id()==elements[i]->get_id())
                    {
                        already_in=true;
                        break;
                    }
                }
            }
            // if it's not already added, then we add it
            if (!already_in)
            {
                this->tetra_list.push_back(elements[i]);
                break;
            }
        }
    }
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