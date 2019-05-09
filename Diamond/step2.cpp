#include "step2.h"

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
    vector<Diamond> diamond_list;
    int diamond_id=0;
    map<tuple<int,int,int>,vector<Diamond*>> external_faces_dict;
    for(pair<tuple<int,int>,vector<Vertex*>> i : edge_to_vertex)
    {
        Diamond tmp= Diamond(diamond_id,edge_dict[i.first],i.second[0]);
        diamond_list.push_back(tmp);
        diamond_id++;
    }

    for(int i=0;i<tetra_list.size();i++)
    {
        if (!tetra_list[i].get_in_diamond())
        {
            Diamond* pointer_diamond;
            vector<Tetrahedron*> pointer_tetra= {&tetra_list[i]};
            Diamond tmp= Diamond(diamond_id,pointer_tetra,tetra_list[i].get_vertices()[0]);
            pointer_diamond = &tmp;
            diamond_list.push_back(tmp);
            diamond_id++;
        }
    }


    for(Diamond &diamond : diamond_list)
    {
        for (tuple<int,int,int> face : diamond.get_external_faces())
        {
            if (external_faces_dict.count(face)==0)
            {
                external_faces_dict.insert({face,{&diamond}});
            }
            else
            {
                external_faces_dict[face].push_back(&diamond);
            }
        }
    }

    for(pair<tuple<int,int,int>,vector<Diamond*>> face : external_faces_dict)
    {
        if(face.second.size()==2)
        {
            face.second[0]->add_neighbour(face.first,face.second[1]);
            face.second[1]->add_neighbour(face.first,face.second[0]);
        }
    }

    // for (tuple<int,int,int> face: diamond_list[18181].get_external_faces())
    // {
    //     cout<<get<0>(face)<<" "<<get<1>(face)<<" "<<get<2>(face)<<endl;
    // }
    // cout<<endl;
    // for (tuple<int,int,int> face: diamond_list[18182].get_external_faces())
    // {
    //     cout<<get<0>(face)<<" "<<get<1>(face)<<" "<<get<2>(face)<<endl;
    // }
    // cout<<endl;
    // for (tuple<int,int,int> face: diamond_list[17843].get_external_faces())
    // {
    //     cout<<get<0>(face)<<" "<<get<1>(face)<<" "<<get<2>(face)<<endl;
    // }

    // for(Diamond &diamond : diamond_list)
    // {
    //     // cout<<diamond.get_neighbours().size()<<endl;
    //     // if (diamond.get_neighbours().size()>4)
    //     {
    //         cout<<diamond.get_id()<<" ";
    //         for (Diamond* neighbour : diamond.get_neighbours())
    //         {
    //             if (neighbour == NULL)
    //             {
    //                 cout<<"NULL ";
    //             }
    //             else
    //             {
    //                 cout<<neighbour->get_id()<<" ";
    //             }
    //         }
    //         cout<<endl;
    //     }   
    // }

    // for(Diamond &diamond : diamond_list)
    // {
    //     // cout<<diamond.get_neighbours().size()<<endl;
    //     if (diamond.get_neighbours().size()>4)
    //     {
    //         int somme=0;
    //         int somme2=0;
    //         for(tuple<int,int,int> face : diamond.get_external_faces())
    //         {
    //             somme+=face_dict[face].size()==1;
    //         }
    //         for(Diamond* diamond : diamond.get_neighbours())
    //         {
    //             somme2+=diamond==NULL;
    //         }
    //         cout<<somme<<" "<<somme2<<endl;
    //     }   
    // }

    return diamond_list;
}