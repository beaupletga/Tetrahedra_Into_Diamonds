#include "../include/save.h"

void save_full_structure_to_mesh(vector<Vertex> &vertex_list,vector<Diamond> &diamond_list, map<tuple<int,int,int>,vector<Tetrahedron*>> &face_dict)
{
    ofstream output;
    output.open ("../data/save_full_structure_to_mesh.mesh");
    output<<"MeshVersionFormatted 1\n";
    output<<"Dimension 3\n";
    output<<"Vertices 1\n";
    output<<vertex_list.size()<<"\n";
    for (Vertex vertex : vertex_list)
    {
        output<<vertex.get_coords()[0]<<" "<<vertex.get_coords()[1]<<" "<<vertex.get_coords()[2]<<"1\n";
    }
    output<<face_dict.size()<<"\n";
    for (pair<tuple<int,int,int>,vector<Tetrahedron*>> face : face_dict)
    {
        output<<get<0>(face.first)<<" "<<get<1>(face.first)<<" "<<get<2>(face.first)<<"1\n";
    }
    output<<diamond_list.size()<<"\n";
    for (Diamond diamond : diamond_list)
    {
        for (int i : diamond.get_vertex_order())
        {
            output<<i<<" ";
        }
        output<<"1\n";
    }
    output.close();
}

void save_full_structure_to_off(vector<Vertex> &vertex_list,vector<Diamond> &diamond_list, map<tuple<int,int,int>,vector<Tetrahedron*>> &face_dict)
{
    ofstream output;
    output.open ("../data/save_full_structure_to_off.off");
    output<<"OFF\n";
    output<<vertex_list.size()<<" "<<diamond_list.size()<<"\n";
    for (Vertex vertex : vertex_list)
    {
        output<<vertex.get_coords()[0]<<" "<<vertex.get_coords()[1]<<" "<<vertex.get_coords()[2]<<"1\n";
    }
    for (Diamond diamond : diamond_list)
    {
        for (int i : diamond.get_vertex_order())
        {
            output<<i<<" ";
        }
        output<<"\n";
    }
    output.close();
}
