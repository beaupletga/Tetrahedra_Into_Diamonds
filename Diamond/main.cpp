#include <iostream>
#include <fstream> 
#include <tuple>
#include <array>
#include <vector>
#include <map>

#include "read_file.h"
#include "Vertex.h"
#include "Triangle.h"
#include "Tetrahedron.h"
#include "preprocessing.h"
#include "visualization.h"
#include "stats.h"
#include "step1.h"
#include "step2.h"

using namespace std;

int main() 
{
    vector<Vertex> vertex_list;
    vector<Tetrahedron> tetra_list;
    tuple<vector<vector<double>>,vector<vector<double>>> result;
    // return both the geometry and the connectivity as a tuple
    // result=read_tet_file("delaunay3D_sphere870.tet");
    result=read_tet_file("hand.tet");
    // result=read_file("delaunay3D_sphere6k.tet");
    // result=read_mesh_file("ball.mesh");

    // read the result tuple and encapsulate the geom. and connect. in propers classes
    preprocessing_tetra(result,vertex_list,tetra_list);

    cout<<"Vertex list size : "<<vertex_list.size()<<endl;
    cout<<"Tetrahedron list size : "<<tetra_list.size()<<endl;

    map<int,vector<Tetrahedron*>> vertex_dict;
    map<tuple<int,int>,vector<Tetrahedron*>> edge_dict;
    map<tuple<int,int,int>,vector<Tetrahedron*>> face_dict;

    make_vertex_dict(tetra_list,vertex_dict);
    make_edge_dict(tetra_list,edge_dict);
    make_face_dict(tetra_list ,face_dict);

    double count_face=0;
    for (Tetrahedron i : tetra_list)
    {
        count_face+=i.get_is_on_boundary();
    }
    cout<<"Share of Tetrahedron on the boundary : "<<count_face/tetra_list.size()<<endl;

    cout<<"Edges dict size : "<<edge_dict.size()<<endl;

    cout<<"Average Vertex Degree : "<<average_vertex_degree(vertex_dict)<<endl;
    cout<<"Average Edge Degree : "<<average_edge_degree(edge_dict)<<endl;
    cout<<"Edges per Vertex : "<<average_edges_per_vertex(vertex_list)<<endl;

    map<tuple<int,int>,vector<Vertex*>> edge_to_vertex;

    edge_to_vertex=step_1_bfs(vertex_list,tetra_list,edge_dict);
    // edge_to_vertex=step_1_edge_degree(vertex_list,tetra_list,edge_dict);
    // edge_to_vertex=step_1_vertex_choose_neighbour(vertex_list,tetra_list,edge_dict);
    

    // this method doesn't work if you use step_1_vertex_choose_neighbour because all diamond are not cycles
    step_2(edge_to_vertex,tetra_list,edge_dict,face_dict);

    // stats(edge_to_vertex,tetra_list);

    visualize_diamond_isolated(vertex_list,tetra_list,edge_dict,edge_to_vertex);
    // visualize(tetra_list);

    return 0;
}  