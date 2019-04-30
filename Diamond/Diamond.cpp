#include "Diamond.h"


Diamond::Diamond(int id,vector<Tetrahedron*>& elements)
{
    // cout<<"d0"<<elements.size()<<endl;
    this->id=id;
    bool already_in=false;
    this->tetra_list.push_back(elements[0]);
    // cout<<"d1"<<endl;
    while (this->tetra_list.size()!=elements.size())
    {
        for(int i=0;i<elements.size();i++)
        {
            // cout<<"d2"<<endl;
            already_in=false;
            // cout<<"ouiii"<<this->tetra_list.back()->get_id()<<endl;
            if (elements[i]->is_adjacent(this->tetra_list.back()))
            {
                // cout<<"oui1"<<endl;
                // cout<<"d3"<<endl;
                for (int j=0;j<this->tetra_list.size();j++)
                {
                    // cout<<"oui2"<<endl;
                    // cout<<"d4"<<endl;
                    if (this->tetra_list[j]->get_id()==elements[i]->get_id())
                    {
                        already_in=true;
                        break;
                    }
                }
            }
            // cout<<"d5"<<endl;
            // cout<<already_in<<endl;
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