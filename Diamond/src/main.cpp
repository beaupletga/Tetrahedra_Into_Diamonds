#include <iostream>
#include <fstream> 
#include <tuple>
#include <array>
#include <vector>
#include <map>

#include "../include/read_file.h"
#include "../include/Vertex.h"
#include "../include/Triangle.h"
#include "../include/Tetrahedron.h"
#include "../include/preprocessing.h"
#include "../include/visualization.h"
#include "../include/navigate.h"
#include "../include/stats.h"
#include "../include/step1.h"
#include "../include/step2.h"
#include "../include/step3.h"
#include "../include/step4.h"

using namespace std;

// dictionnaire de vertex (int,numero_diamant), ref vers un diamant adjacent

// array de tetra (int,numero_diamant), chaque tetra est associé avec un numero

// array de diamant (int,tableau_numero_diamant_voisin), où le diamant a juste une liste de ref vers ses voisins


int main() 
{
    vector<Vertex> vertex_list;
    vector<Tetrahedron> tetra_list;
    tuple<vector<vector<double>>,vector<vector<double>>> result;
    // return both the geometry and the connectivity as a tuple
    // result=read_tet_file("../data/delaunay3D_sphere870.tet");
    // result=read_tet_file("../data/hand.tet");
    // result=read_tet_file("../data/delaunay3D_sphere6k.tet");
    result=read_mesh_file("../data/ball.mesh");

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

    cout<<"Tetra per Vertex : "<<average_vertex_degree(vertex_dict)<<endl;
    cout<<"Tetra per edge : "<<average_edge_degree(edge_dict)<<endl;
    cout<<"Edges per Vertex : "<<average_edges_per_vertex(vertex_list)<<endl;

    map<tuple<int,int>,vector<Vertex*>> edge_to_vertex;

    edge_to_vertex=step_1_bfs(vertex_list,tetra_list,edge_dict);
    // edge_to_vertex=step_1_edge_degree(vertex_list,tetra_list,edge_dict);
    // edge_to_vertex=step_1_vertex_choose_neighbour(vertex_list,tetra_list,edge_dict);
    

    // this method doesn't work if you use step_1_vertex_choose_neighbour because all diamond are not cycles
    vector<Diamond> diamond_list=step_2(edge_to_vertex,tetra_list,edge_dict,face_dict);

    // stats(edge_to_vertex,tetra_list);

    // visualize_diamond_isolated(vertex_list,tetra_list,edge_dict,edge_to_vertex);
    // visualize_all(vertex_list,tetra_list);
    // visualize(tetra_list);

    // for each tetra, we assign its position in the diamond array
    int tetra_array[tetra_list.size()];

    int diamond1_size=count_if(diamond_list.begin(),diamond_list.end(),[](Diamond i){return i.get_tetra_list().size()==1;});
    int diamond3_size=count_if(diamond_list.begin(),diamond_list.end(),[](Diamond i){return i.get_tetra_list().size()==3;});
    int diamond4_size=count_if(diamond_list.begin(),diamond_list.end(),[](Diamond i){return i.get_tetra_list().size()==4;});
    int diamond5_size=count_if(diamond_list.begin(),diamond_list.end(),[](Diamond i){return i.get_tetra_list().size()==5;});
    int diamond6_size=count_if(diamond_list.begin(),diamond_list.end(),[](Diamond i){return i.get_tetra_list().size()==6;});
    int diamond7_size=count_if(diamond_list.begin(),diamond_list.end(),[](Diamond i){return i.get_tetra_list().size()==7;});
    int diamond8_size=count_if(diamond_list.begin(),diamond_list.end(),[](Diamond i){return i.get_tetra_list().size()==8;});
    int diamond9_size=count_if(diamond_list.begin(),diamond_list.end(),[](Diamond i){return i.get_tetra_list().size()==9;});

    // array gathering all neighbours of the diamonds
    int array_size=diamond1_size*4+diamond3_size*6+diamond4_size*8+diamond5_size*10+
    diamond6_size*12+diamond7_size*14+diamond8_size*16+diamond9_size*18;
    int diamond_array[array_size];

    // 1 if it's a new diamond, 0 ow
    // we dont count this array at the end because we can include each value as a reference bit into the diamond_array
    bool diamond_extra_bytes_array[array_size]={0};

    set_central_edge(diamond_list,edge_dict,vertex_dict);

    unordered_set<int> v;
    for(Diamond &diamond : diamond_list)
    {
        // cout<<diamond.get_central_edge().first<<" "<<diamond.get_central_edge().second<<endl;
        v.insert(diamond.get_central_edge().first);
        v.insert(diamond.get_central_edge().second);
    }

    cout<<(double)v.size()/vertex_list.size()<<endl;

    cout<<"Nb Diamonds : "<<diamond_list.size()<<endl;
    int x=0;
    // for(int i=0;i<diamond_list.size();i++)
    // {
    //     if (diamond_list[i].has_anchor)
    //     {
    //        x++;
    //     }
    // }
    // cout<<"Nb Diamonds with anchor : "<<x<<endl;

    // for(Tetrahedron* tetra : vertex_dict[2839])
    // {
    //     tetra->display_vertices_id();
    // }

    x=0;
    for(int i=0;i<diamond_list.size();i++)
    {
        x+=diamond_list[i].get_tetra_list().size();
    }
    cout<<x<<endl;

    step_3(diamond_list,vertex_list,vertex_dict);

    x=0;
    unordered_set<int> s;
    for(int i=0;i<diamond_list.size();i++)
    {
        if (diamond_list[i].has_anchor)
        {
            // s[diamond_list[i].get_anchor_vertex()->get_id()]+=1;
            s.insert(diamond_list[i].get_anchor_vertex()->get_id());
            
        }
        x+=diamond_list[i].get_tetra_list().size();
    }
    cout<<s.size()<<endl;
    cout<<x<<endl;
    // map<int,int> index_to_diamond_id = step_4(tetra_list,diamond_list,tetra_array,diamond_array,diamond_extra_bytes_array,array_size);

    // vector<int> path= BFS(diamond_array,diamond_extra_bytes_array,array_size);

    // cout<<"Array size : "<<array_size<<endl;
    // cout<<path.size()<<endl;
    // float size = (float)(array_size+tetra_list.size())/(float)tetra_list.size();
    // cout<<"Real Size : "<<size<<endl;


    // visualize_diamond(vertex_list,tetra_list,diamond_list,path);  
    // visualize_central_edges(vertex_list,diamond_list);

    

    return 0;
}