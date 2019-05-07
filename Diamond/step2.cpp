#include "step2.h"

// This second step consist in linking diamond (and isolated tetra) for adjacency relations
// We take a set of edges and their anchor, and return a vector of diamond


vector<Diamond> step_2(map<tuple<int,int>,vector<Vertex*>>& edge_to_vertex,vector<Tetrahedron>& tetra_list,map<tuple<int,int>,vector<Tetrahedron*>>& edge_dict)
{
    vector<Diamond> diamond_list;
    int diamond_id=0;
    double count_average_cycle_size=0;
    for(pair<tuple<int,int>,vector<Vertex*>> i : edge_to_vertex)
    {
        Diamond tmp= Diamond(diamond_id,edge_dict[i.first]);
        diamond_list.push_back(tmp);
        diamond_id++;
        count_average_cycle_size+=edge_dict[i.first].size();
    }
    cout<<"Diamond average size : "<<count_average_cycle_size/diamond_list.size()<<endl;
    return diamond_list;
}