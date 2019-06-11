#include "../include/step2.h"

// This second step consist in linking diamond (and isolated tetra) for adjacency relations
// We take a set of edges and their anchor, and return a vector of diamond

// pour chaque diamond :
//  - taille (nb de tetra)
//  - contient les tetra
//  -- reference vers tous voisins 

// pour chaque tetra : 
//  -- reference vers le Diamond (int)
//  -- position dans le diamand (3 bits)

// pour chaque vertex :
//  -- reference vers un diamand ou un tetra isolé


vector<Diamond> step_2(map<tuple<int,int>,vector<Vertex*>>& edge_to_vertex,vector<Tetrahedron>& tetra_list,map<tuple<int,int>,vector<Tetrahedron*>>& edge_dict,map<tuple<int,int,int>,vector<Tetrahedron*>>& face_dict)
{
    int count1,count2=0;
    vector<Diamond> diamond_list;
    int diamond_id=0;
    
    // create diamond for each edge selected in step 1
    for(pair<tuple<int,int>,vector<Vertex*>> i : edge_to_vertex)
    {
        Diamond tmp= Diamond(diamond_id,edge_dict[i.first],i.second[0]);
        diamond_list.push_back(tmp);
        // for(int j=0;j<diamond_list.back().get_tetra_list().size();j++)
        // {
        //     diamond_list.back().get_tetra_list()[j]->set_position_in_diamond(j);
        //     diamond_list.back().get_tetra_list()[j]->set_diamond_ref(&diamond_list.back());
        // }
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
    for(Diamond &diamond : diamond_list)
    {
        for(int i=0;i<diamond.get_tetra_list().size();i++)
        {
            diamond.get_tetra_list()[i]->set_position_in_diamond(i);
            diamond.get_tetra_list()[i]->set_diamond_ref(&diamond);
        }
    }
    return diamond_list;
}