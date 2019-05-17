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

void stats(map<tuple<int,int>,vector<Vertex*>>& edge_to_vertex,vector<Tetrahedron>& tetra_list)
{
    double count_failure=0;
    double count_tetra_isolated=0;
    int count_edges_in_tetra;
    double b=0;
    for (Tetrahedron &i : tetra_list)
    {
        vector<tuple<int,int>> edges = i.enumerate_edges();
        // i.display_edges();S
        count_edges_in_tetra=0;
        for (tuple<int,int> j : edges)
        {
            if (edge_to_vertex.count(j)!=0)
            {
                count_edges_in_tetra++;
                i.count_matched++;
            }
        }
        if (count_edges_in_tetra>1)
        {
            count_failure++;
        }
        if (count_edges_in_tetra==0)
        {
            count_tetra_isolated++;
            if (i.get_is_on_boundary())
            {
                b++;
            }
        }
    }
    cout<<b/tetra_list.size()<<endl;
    cout<<"Share of Tetra isolated : "<<count_tetra_isolated/tetra_list.size()<<endl;
    cout<<"Share of tetrahedra having at least 2 edges taken : "<<count_failure/tetra_list.size()<<endl;

    double edge_count_twice=0;
    for (pair<tuple<int,int>,vector<Vertex*>> i :edge_to_vertex)
    {
        if (i.second.size()>1)
        {
            edge_count_twice++;
        }
    }

    cout<<"Share of edges choosen by both extreme vertex : "<<edge_count_twice<<endl;

    double count_tetra_diamond=0;
    for (int i=0;i<tetra_list.size();i++)
    {
        count_tetra_diamond+=tetra_list[i].get_in_diamond();
    }
    cout<<"Share of tetra in full diamond : "<<count_tetra_diamond/tetra_list.size()<<endl;

    count_tetra_isolated=0;
    for (Tetrahedron tetra : tetra_list)
    {
        if (tetra.get_in_diamond()==false )
        {
            count_tetra_isolated++;
        }
    }
    cout<<"Share of tetra isolated: "<<count_tetra_isolated/tetra_list.size()<<endl;

    double count_tetra_in_diamond_boundary=0;
    for (Tetrahedron tetra : tetra_list)
    {
        if (tetra.get_in_diamond()==false and tetra.get_is_on_boundary())
        {
            count_tetra_in_diamond_boundary++;
        }
    }
    cout<<"Share of tetra isolated and on the boundary : "<<count_tetra_in_diamond_boundary/tetra_list.size()<<endl;


    cout<<"Theorical Size : "<<2*count_tetra_diamond/tetra_list.size()+4*count_tetra_isolated/tetra_list.size()<<endl;
}