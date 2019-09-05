#include "../include/step2.h"

// This second step consists in linking diamond (and isolated tetra) for adjacency relations
// We take a set of central edges (from step 1) and create diamonds for each central edge
// if a tetra is not in a diamond, we also create a diamond (but of size 1)
vector<Diamond> step_2(map<tuple<int,int>,vector<Tetrahedron*>>& edge_to_tetra,vector<Tetrahedron>& tetra_list,
map<tuple<int,int>,vector<Tetrahedron*>>& edge_dict,map<tuple<int,int,int>,vector<Tetrahedron*>>& face_dict,
vector<Vertex> &vertex_list)
{
    int count1,count2=0;
    vector<Diamond> diamond_list;
    int diamond_id=0;
    
    // create diamond for each edge selected in step 1
    for(pair<tuple<int,int>,vector<Tetrahedron*>> i : edge_to_tetra)
    {
        Diamond tmp= Diamond(diamond_id,edge_dict[i.first],&vertex_list[get<0>(i.first)]);
        diamond_list.push_back(tmp);
        diamond_id++;
    }

    // create diamond for each isolated tetra
    // in this case, a diamond is just a tetra
    for(int i=0;i<tetra_list.size();i++)
    {
        if (!tetra_list[i].get_in_diamond())
        {
            Diamond* pointer_diamond;
            vector<Tetrahedron*> pointer_tetra= {&tetra_list[i]};
            Diamond tmp= Diamond(diamond_id,pointer_tetra,tetra_list[i].get_vertices()[rand()%4]);
            pointer_diamond = &tmp;
            diamond_list.push_back(tmp);
            // diamond_list.back().get_tetra_list()[0]->set_position_in_diamond(0);
            // diamond_list.back().get_tetra_list()[0]->set_diamond_ref(&diamond_list.back());
            diamond_id++;
        }
    }


    // set for each tetra, the ref toward its diamond
    for(Diamond &diamond : diamond_list)
    {
        for(int i=0;i<diamond.get_tetra_list().size();i++)
        {
            // diamond.get_tetra_list()[i]->set_position_in_diamond(i);
            diamond.get_tetra_list()[i]->set_diamond_ref(&diamond);
        }
    }
    return diamond_list;
}