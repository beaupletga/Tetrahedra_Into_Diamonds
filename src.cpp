#include "src.h"

// read a set of vertices and return all possible edges
vector<tuple<int,int>> enumerate_edges(vector<Vertex> vertices)
{
    vector<tuple<int,int>> edges;
    for(int i=0;i<vertices.size()-1;i++)
    {
        for (int j=i+1;j<vertices.size();j++)
        {
            tuple<int,int> tmp=make_tuple(vertices[i].get_id(),vertices[j].get_id());
            edges.push_back(tmp);
        }
    }
    return edges;
}


std::map<int,vector<Tetrahedron *>> make_vertex_dict(vector<Tetrahedron> tetra_list)
{
    std::map<int,vector<Tetrahedron *>> vertex_dict;
    // iterate over the triangles and add the 3 edges into edge_dict
    for(int i=0;i<tetra_list.size();i++)
    {
        for (Vertex j : tetra_list[i].get_vertices())
        {
            if(vertex_dict.count(j.get_id())==0)
            {
                vector<Tetrahedron *> tmp={&tetra_list[i]};
                vertex_dict.insert(std::pair<int,vector<Tetrahedron *>>(j.get_id(),tmp));
            }
            else
            {
                vertex_dict.find(j.get_id())->second.push_back(&tetra_list[i]);
            }
        }
    }
    return vertex_dict;
}


std::map<tuple<int,int>,vector<Tetrahedron *>> make_edge_dict(vector<Tetrahedron> tetra_list)
{
    // each edge is a tuple of vertice and belong to at least 1 tetra
    std::map<tuple<int,int>,vector<Tetrahedron *>> edge_dict;
    // iterate over the triangles and add the 3 edges into edge_dict
    for(int i=0;i<tetra_list.size();i++)
    {
        for (tuple<int,int> j : enumerate_edges(tetra_list[i].get_vertices()))
        {
            if(edge_dict.count(j)==0)
            {
                vector<Tetrahedron *> tmp={&tetra_list[i]};
                edge_dict.insert(pair<tuple<int,int>,vector<Tetrahedron *>>(j,tmp));
            }
            else
            {
                edge_dict.find(j)->second.push_back(&tetra_list[i]);
            }
        }
    }
    return edge_dict;
}

// vertex_list and tetra_list are empty
// read result which is a tuple containing both the geometry and connectivity
// encapsulate both into proper classes
void preprocessing_tetra(tuple<vector<vector<double>>,vector<vector<double>>> result, vector<Vertex>& vertex_list, vector<Tetrahedron>& tetra_list)
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
        vector<Vertex> tmp0 ={vertex_list[connectivity[i][0]],vertex_list[connectivity[i][1]],vertex_list[connectivity[i][2]],vertex_list[connectivity[i][3]]};
        Tetrahedron tmp1=Tetrahedron(i,tmp0);
        tetra_list.push_back(tmp1);
    }
}   


    
// map<tuple<int,int>,vector<Tetrahedron>>::iterator it;
//     for ( it = edge_dict.begin(); it != edge_dict.end(); it++ )
//     {
//         for (int i=0;i<it->second.size()-1;i++)
//         {
//             for (int j=i+1;j<it->second.size();j++)
//             {
//                 it->second[i].get_neighbours().push_back(it->second[j]);
//                 it->second[j].get_neighbours().push_back(it->second[i]);
//             }
//         }
//     }


    





