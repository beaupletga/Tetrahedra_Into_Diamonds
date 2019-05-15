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
#include "step3.h"

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
    // result=read_tet_file("delaunay3D_sphere870.tet");
    // result=read_tet_file("hand.tet");
    // result=read_tet_file("delaunay3D_sphere6k.tet");
    result=read_mesh_file("ball.mesh");

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
    vector<Diamond> diamond_list=step_2(edge_to_vertex,tetra_list,edge_dict,face_dict);

    stats(edge_to_vertex,tetra_list);

    visualize_diamond_isolated(vertex_list,tetra_list,edge_dict,edge_to_vertex);
    // visualize_all(vertex_list,tetra_list);
    // visualize(tetra_list);

    // cout<<max_element(diamond_list.begin(),diamond_list.end(),[](Diamond i,Diamond j){return i.get_tetra_list().size()<j.get_tetra_list().size();})->get_tetra_list().size()<<endl;

    


    // double count=0;
    // for(Tetrahedron tetra : tetra_list)
    // {
    //     if (!tetra.get_in_diamond())
    //     {
    //         for (Tetrahedron* neighbour : tetra.get_neighbours())
    //         {
    //             if (!neighbour->get_in_diamond())
    //             {
    //                 count++;
    //                 break;
    //             }
    //         }
    //     }
    // }
    // cout<<"Tetra isolated adjacent : "<<count/tetra_list.size()<<endl;

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

    map<int,int> diamond_id_to_index = step_3(tetra_list,diamond_list,tetra_array,diamond_array,diamond_extra_bytes_array,array_size);

    map<int,int> index_to_diamond_id;
    for(pair<int,int> i : diamond_id_to_index)
    {
        index_to_diamond_id[i.second]=i.first;
    }

    vector<int> path;
    queue<int> wait_list;
    unordered_set<int> lala;
    wait_list.push(0);
    int w=0;
    while(!wait_list.empty())
    {
        int index = wait_list.front();
        wait_list.pop();
        int i=index+1;
        if(lala.count(index_to_diamond_id[index])==0)
        {
            wait_list.push(diamond_array[index]);
            lala.insert(index_to_diamond_id[index]);
            path.push_back(index_to_diamond_id[index]);
            while(diamond_extra_bytes_array[i]!=1 && i<array_size)
            {
                if (diamond_array[i]!=-1)
                {
                    wait_list.push(diamond_array[i]);
                }
                i++;
            }
        }
        w++;
        if (w==10000){
            break;
        }
    }

    cout<<"Array size : "<<array_size<<endl;
    cout<<"lala size : "<<lala.size()<<" "<<diamond_list.size()<<endl;
    cout<<path.size()<<endl;
    visualize_diamond(vertex_list,tetra_list,diamond_list,path);  


    return 0;
}  