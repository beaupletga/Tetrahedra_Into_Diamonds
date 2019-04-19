#include "src.h"

// vertex_list and tetra_list are empty
// read result which is a tuple containing both the geometry and connectivity
// encapsulate both into proper classes
void preprocessing_tetra(tuple<vector<vector<double>>,vector<vector<double>>>& result, vector<Vertex>& vertex_list, vector<Tetrahedron>& tetra_list)
{
    vector<vector<double>> geometry = get<0>(result);
    vector<vector<double>> connectivity = get<1>(result);

    for(int i=0;i<geometry.size();i++)
    {
        Vertex tmp=Vertex(i,geometry[i]);
        vertex_list.push_back(tmp);
    }

    for(int i=0;i<connectivity.size();i++)
    {
        vector<Vertex*> tmp0 ={&vertex_list[connectivity[i][0]],&vertex_list[connectivity[i][1]],&vertex_list[connectivity[i][2]],&vertex_list[connectivity[i][3]]};
        Tetrahedron tmp1=Tetrahedron(i,tmp0);
        tetra_list.push_back(tmp1);

        tmp0[0]->add_neighbours(tmp0);
        tmp0[1]->add_neighbours(tmp0);
        tmp0[2]->add_neighbours(tmp0);
        tmp0[3]->add_neighbours(tmp0);
    }
}   


// make a dict of <id of vertex,pointers towards tetra containing this vertex>
void make_vertex_dict(vector<Tetrahedron> &tetra_list,map<int,vector<Tetrahedron*>>& vertex_dict)
{
    // iterate over the triangles and add the 3 edges into edge_dict
    for(int i=0;i<tetra_list.size();i++)
    {
        for (Vertex* j : tetra_list[i].get_vertices())
        {
            if(vertex_dict.count(j->get_id())==0)
            {
                vector<Tetrahedron*> tmp={&tetra_list[i]};
                vertex_dict.insert(std::pair<int,vector<Tetrahedron*>>(j->get_id(),tmp));
            }
            else
            {
                vertex_dict.find(j->get_id())->second.push_back(&tetra_list[i]);
            }
        }
    }
}

// make a dict of <edge,pointers towards tetra containing this edge>
// where edge is a tuple <id of vertex,id of vertex> which are both int
void make_edge_dict(vector<Tetrahedron>& tetra_list,map<tuple<int,int>,vector<Tetrahedron*>>& edge_dict)
{
    // each edge is a tuple of vertice and belong to at least 1 tetra
    // std::map<tuple<int,int>,vector<Tetrahedron*>> edge_dict;
    // iterate over the triangles and add the 3 edges into edge_dict
    for(int i=0;i<tetra_list.size();i++)
    {
        vector<tuple<int,int>> edges = tetra_list[i].enumerate_edges();
        for (int j=0;j<edges.size();j++)
        {
            // cout<<get<0>(edges[j])<<" "<<get<1>(edges[j]);
            if(edge_dict.count(edges[j])==0)
            {
                vector<Tetrahedron*> tmp={&tetra_list[i]};
                edge_dict.insert(pair<tuple<int,int>,vector<Tetrahedron *>>(edges[j],tmp));
            }
            else
            {
                edge_dict.find(edges[j])->second.push_back(&tetra_list[i]);
            }
            // cout<<endl;
        }
    }
}

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
double average_edge_degree(std::map<tuple<int,int>,vector<Tetrahedron *>> edge_dict)
{
    double count=0;

    for (std::pair<tuple<int,int>, vector<Tetrahedron *>> element : edge_dict) 
    {		
        count+=element.second.size();
	}
    return count/edge_dict.size();
}

// how many edges per vertex
double average_edges_per_vertex(vector<Vertex> vertex_list)
{
    double count=0;

    for (Vertex element : vertex_list) 
    {		
        count+=element.get_neighbours().size();
	}
    return count/vertex_list.size();
}

Vertex* pick_random_neighbour(Vertex& vertex)
{
    int vertex_index =rand() % vertex.get_neighbours().size();
    return vertex.get_neighbours()[vertex_index];
}

bool cmp(Vertex* lhs, Vertex* rhs)
{
  return lhs->get_coords()[2] < rhs->get_coords()[2];
}

Vertex* pick_steepest_neighbour(Vertex& vertex)
{
    vector<Vertex*> neighbours=vertex.get_neighbours();
    return *max_element(neighbours.begin(),neighbours.end(),cmp);
}

void step_1(vector<Vertex>& vertex_list,vector<Tetrahedron>& tetra_list)
{
    map<tuple<int,int>,vector<Vertex*>> edge_to_vertex;
    for(int i=0;i<vertex_list.size();i++)
    {
        Vertex* v2 =pick_random_neighbour(vertex_list[i]);
        tuple<int,int> tmp;
        if (vertex_list[i].get_id()<v2->get_id())
        {
            tmp= make_tuple(vertex_list[i].get_id(),v2->get_id());
        }
        else
        {
            tmp= make_tuple(v2->get_id(),vertex_list[i].get_id());
        }
        if (edge_to_vertex.count(tmp)==0)
        {
            vector<Vertex*> vec_tmp={&vertex_list[i]};
            edge_to_vertex.insert({tmp,vec_tmp});
        }
        else
        {
            edge_to_vertex.find(tmp)->second.push_back(&vertex_list[i]);
        }
    }

    double count_failure=0;
    int count_edges_in_tetra;
    for (Tetrahedron &i : tetra_list)
    {
        vector<tuple<int,int>> edges = i.enumerate_edges();
        // i.display_edges();
        count_edges_in_tetra=0;
        for (tuple<int,int> j : edges)
        {
            // cout<<get<0>(j)<<" "<<get<1>(j)<<endl;
            if (edge_to_vertex.count(j)!=0)
            {
                count_edges_in_tetra++;
            }
        }
        // cout<<count_edges_in_tetra<<endl;
        if (count_edges_in_tetra>1)
        {
            count_failure++;
        }
    }

    cout<<"Share of tetrahedra having at least 2 edges taken : "<<count_failure/tetra_list.size()<<endl;

    double edge_count_twice=0;
    for (pair<tuple<int,int>,vector<Vertex*>> i :edge_to_vertex)
    {
        if (i.second.size()>1)
        {
            edge_count_twice++;
        }
    }

    cout<<"Share of edges choosen by both etreme vertex : "<<edge_count_twice<<endl;
}


    





