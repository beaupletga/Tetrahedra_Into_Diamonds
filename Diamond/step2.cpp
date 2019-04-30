#include "step2.h"


vector<Diamond> step_2(map<tuple<int,int>,vector<Vertex*>>& edge_to_vertex,vector<Tetrahedron>& tetra_list,map<tuple<int,int>,vector<Tetrahedron*>>& edge_dict)
{
    vector<Diamond> diamond_list;
    int diamond_id=0;
    double count_is_cyle=0;
    double tetra_in_full_diamond=0;
    for(pair<tuple<int,int>,vector<Vertex*>> i : edge_to_vertex)
    {
        if (is_cycle(edge_dict[i.first]))
        {
            count_is_cyle++;
            tetra_in_full_diamond+=edge_dict[i.first].size();
            // cout<<"oui3"<<endl;
            for (Tetrahedron* j : edge_dict[i.first])
            {
                j->set_in_diamond(true);
            }
        }
        // else
        // {
        //     for(Tetrahedron* j : edge_dict[i.first])
        //     {
        //         j->display_vertices_id();
        //     }
        //     // assert(true==false);
        //     cout<<endl;
        // }
        
        Diamond tmp= Diamond(diamond_id,edge_dict[i.first]);
        diamond_list.push_back(tmp);
    }
    cout<<"Share of full diamond  : "<<count_is_cyle/edge_to_vertex.size()<<endl;
    // cout<<"Share of tetra in full diamond : "<<tetra_in_full_diamond/tetra_list.size()<<endl;
    return diamond_list;
}