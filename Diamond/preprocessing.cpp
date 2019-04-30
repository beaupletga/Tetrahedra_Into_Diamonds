#include "preprocessing.h"
#include <cassert>


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
                vertex_dict.insert({j->get_id(),tmp});
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
                edge_dict.insert({edges[j],tmp});
            }
            else
            {
                Tetrahedron* tmp=&tetra_list[i];
                edge_dict.find(edges[j])->second.push_back(tmp);
            }
            // cout<<endl;
        }
    }
}

// make a dict of <edge,pointers towards tetra containing this edge>
// where edge is a tuple <id of vertex,id of vertex> which are both int
void make_face_dict(vector<Tetrahedron>& tetra_list,map<tuple<int,int,int>,vector<Tetrahedron*>>& face_dict)
{
    // each face is a triplet of vertice and belong to at least 1 tetra
    // iterate over the triangles and add the 4 faces into face_dict
    for(int i=0;i<tetra_list.size();i++)
    {
        vector<tuple<int,int,int>> faces = tetra_list[i].enumerate_faces();
        for (int j=0;j<faces.size();j++)
        {
            if(face_dict.count(faces[j])==0)
            {
                vector<Tetrahedron*> tmp={&tetra_list[i]};
                face_dict.insert({faces[j],tmp});
            }
            else
            {
                face_dict.find(faces[j])->second.push_back(&tetra_list[i]);
            }
        }
    }
    for(pair<tuple<int,int,int>,vector<Tetrahedron*>> i : face_dict)
    {
        if (i.second.size()==1)
        {
            i.second[0]->set_is_on_boundary(true);
        }
    }

}