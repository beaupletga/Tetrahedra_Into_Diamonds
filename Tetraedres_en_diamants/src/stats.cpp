#include "../include/stats.h"

// in average, how many tetra are adjacents to a vertex
double average_vertex_degree(std::map<int,vector<Tetrahedron*>>& vertex_dict)
{
    double count=0;

    for (std::pair<int, vector<Tetrahedron*>> element : vertex_dict) 
    {		
        count+=element.second.size();
	}
    return count/vertex_dict.size();
}

// in average, how many tetra are adjacents to a vertex
double average_edge_degree(std::map<tuple<int,int>,vector<Tetrahedron *>>& edge_dict)
{
    double count=0;

    for (std::pair<tuple<int,int>, vector<Tetrahedron *>> element : edge_dict) 
    {		
        count+=element.second.size();
	}
    return count/edge_dict.size();
}

// how many edges per vertex
double average_edges_per_vertex(vector<Vertex>& vertex_list)
{
    double count=0;

    for (Vertex element : vertex_list) 
    {		
        count+=element.get_neighbours().size();
	}
    return count/vertex_list.size();
}

void stats(map<tuple<int,int>,vector<Tetrahedron*>>& edge_to_tetra,vector<Tetrahedron>& tetra_list)
{
    double boundary_tetra = count_if(tetra_list.begin(),tetra_list.end(),
    [](Tetrahedron tetra){return tetra.get_is_on_boundary();});
    cout<<"Share of tetra on the boundary : "<<boundary_tetra/tetra_list.size()<<endl;

    double isolated_tetra = count_if(tetra_list.begin(),tetra_list.end(),
    [](Tetrahedron tetra){return tetra.get_diamond_ref()->get_tetra_list().size()==1;});
    cout<<"Share of isolated tetra : "<<isolated_tetra/tetra_list.size()<<endl;

    double tetra_in_diamond = count_if(tetra_list.begin(),tetra_list.end(),
    [](Tetrahedron tetra){return tetra.get_diamond_ref()->get_tetra_list().size()>1;});
    cout<<"Share of tetra in full diamond : "<<tetra_in_diamond/tetra_list.size()<<endl;
    
    cout<<"Theorical Size : "<<2*tetra_in_diamond/tetra_list.size()+4*isolated_tetra/tetra_list.size()<<endl;
}