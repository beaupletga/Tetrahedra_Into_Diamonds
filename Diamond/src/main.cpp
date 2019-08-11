#include <iostream>
#include <fstream> 
#include <tuple>
#include <array>
#include <vector>
#include <math.h>
#include <map>
#include <chrono> 

#include "../include/read_file.h"
#include "../include/Vertex.h"
#include "../include/Triangle.h"
#include "../include/Tetrahedron.h"
#include "../include/preprocessing.h"
#include "../include/visualization.h"
#include "../include/navigate.h"
#include "../include/consistency.h"
#include "../include/benchmark.h"
#include "../include/stats.h"
#include "../include/step1.h"
#include "../include/step2.h"
#include "../include/step3.h"
#include "../include/step4.h"

using namespace std;


// to do : 

// done // - utiliser les bits de services pour naviguer dans le graphe
// done // - calculer le degré d'un sommet
// done // - calculer l'hypersphere d'un sommet
// comparer appariement des diamants et des quads et comparer les ref necessaires (une economisé par quad et 2 quand diamant)
// - visualiser les edges pour appareiller les diamants avec des ancres (pour le rapport)
// - comprendre l'article SOT (pour le rapport)
// - reordonner les tetra afin que l'on puisse passer d'un tetra à un diamant
// - améliorer l'algo pour creer des diamants (utiliser un algo d'optimisation local)
// - préciser dans le rapport que notre algo est streaming (puisque le BFS ne lit que quelque tetra à la fois)
// - utiliser les references differentielles pour gagner de la place (plutot que de stocker les references sur 32 bits, 
// on peut stocker la différence entre deux référence sur 8 ou 16 bits)
// - faire une reduction polynomiale afin de montrer que notre probleme est np-complet
// faire une fonction qui permet d'encoder notre structure dans un fichier off

int main(int argc, char** argv) 
{
    vector<Vertex> vertex_list;
    vector<Tetrahedron> tetra_list;
    tuple<vector<vector<double>>,vector<vector<double>>> result;

    if (argc==1)
    {
        return 0;
    }
    else
    {
        try
        {
            string filename =argv[1]; 
            if (filename.substr(filename.length()-4)=="mesh")
            {
                result=read_mesh_file(filename);
            }
            else if (filename.substr(filename.length()-3)=="tet")
            {
                result=read_tet_file(filename);
            }
            
            
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << endl;
            return 0;
        }        
    }
    
    
    // return both the geometry and the connectivity as a tuple
    // result=read_tet_file("../data/delaunay3D_sphere870.tet");
    // result=read_tet_file("../data/hand.tet");
    // result=read_tet_file("../data/delaunay3D_sphere6k.tet");
    
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
    
    map<tuple<int,int>,vector<Tetrahedron*>> edge_to_tetra;


    // edge_to_tetra=step_1_bfs(vertex_list,tetra_list,edge_dict);
    auto start = chrono::high_resolution_clock::now(); 
    edge_to_tetra=step_1_bfs(vertex_list,tetra_list,edge_dict);
    return 0;
    // edge_to_tetra=step_1_random(vertex_list,tetra_list,edge_dict);
    // edge_to_tetra=step_1_edge_degree(vertex_list,tetra_list,edge_dict);
    // edge_to_vertex=step_1_vertex_choose_neighbour(vertex_list,tetra_list,edge_dict);
    auto stop = chrono::high_resolution_clock::now(); 
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start); 
    cout<<"Time for creating Diamonds : "<<duration.count()*1e-6<<" s"<<endl;

    

    // this method doesn't work if you use step_1_vertex_choose_neighbour because all diamond are not cycles
    vector<Diamond> diamond_list=step_2(edge_to_tetra,tetra_list,edge_dict,face_dict,vertex_list);

    cout<<"Diamond list size : "<<diamond_list.size()<<endl;

    // check_1(diamond_list);
    // check_3(diamond_list);
    // vector<int> tetras_id= {3589,5208,10131,5575,14914,11636,16268};

    // 3589
    // 5208
    // 10131
    // 5575
    // 14914
    // 11636
    // 16268

    // for (Tetrahedron* tetra : diamond_list[2625].get_tetra_list())
    // {
    //     tetra->display_vertices_id();
    // }    
    // visualize_subset_tetra(vertex_list,tetra_list,tetras_id);
    // visualize_subset_diamond(vertex_list,diamond_list,ids);
    // return 0;

    stats(edge_to_tetra,tetra_list);
    // return 0;

    // visualize_diamond_isolated(vertex_list,tetra_list,edge_dict,edge_to_vertex);
    // visualize_all(vertex_list,tetra_list);
    // vector<int> tetras_id;
    // for(int i=0;i<tetra_list.size();i++)
    // {
    //     tetras_id.push_back(i);
    // }
    // visualize_subset_tetra(vertex_list,tetra_list,tetras_id);
    
    cout<<"Step3"<<endl;
    start = chrono::high_resolution_clock::now(); 
    // edge_to_tetra=step_1_random(vertex_list,tetra_list,edge_dict);
    step_3_0_set_central_edge(diamond_list,edge_dict,vertex_dict);
    cout<<1<<endl;
    step_3_1_pair_vertices_as_anchor(diamond_list,vertex_list,vertex_dict,edge_dict);
    cout<<1<<endl;
    step_3_2_pair_unpaired_vertices(diamond_list,vertex_list,vertex_dict);
    cout<<1<<endl;
    step_3_3_connectivity(diamond_list);
    cout<<1<<endl;
    stop = chrono::high_resolution_clock::now(); 
    duration = chrono::duration_cast<chrono::microseconds>(stop - start); 
    cout<<"Time for choosing central edges and pair vertice with diamond : "<<duration.count()*1e-6<<" s"<<endl;
    map<int,Diamond*> anchor_dict=step_3_4_anchor_dict(diamond_list);
    

    // vector<int> isolated_diamond_ids;
    // for (int i=0;i<diamond_list.size();i++)
    // {
    //     if (diamond_list[i].get_tetra_list().size()>1)
    //     {
    //         isolated_diamond_ids.push_back(diamond_list[i].get_id());
    //     }
    // }
    // visualize_subset_diamond(vertex_list,diamond_list,isolated_diamond_ids);
    // visualize(tetra_list);
    // visualize_central_edges(vertex_list,diamond_list);


    return 0;
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

    cout<<"attention "<<count_if(diamond_list.begin(),diamond_list.end(),[](Diamond i){return i.get_tetra_list().size()>9;})<<endl;
    
    // array gathering all neighbours of the diamonds
    int array_size=diamond1_size*4+diamond3_size*6+diamond4_size*8+diamond5_size*10+
    diamond6_size*12+diamond7_size*14+diamond8_size*16+diamond9_size*18;
    int diamond_array[array_size];
    
    // 1 if it's a new diamond, 0 ow
    // we dont count this array at the end because we can include each value as a reference bit into the diamond_array
    bool diamond_extra_bytes_array[array_size]={0};

    cout<<"Array size : "<<array_size<<endl;
    
    step_3_5_set_neighbour_permutation(diamond_list);

    // vector<tuple<int,int,int>> permutation_array(array_size,tuple<int,int,int>{0,0,0});
    // vector<tuple<int,int,int>> face_array(array_size,tuple<int,int,int>{0,0,0});
    vector<tuple<int,int,int>> permutation_array;
    vector<tuple<int,int,int>> face_array;

    for (tuple<int,int,int> face : face_array)
    {
        if (get<0>(face)==0 && get<1>(face)==0 && get<2>(face)==1)
        {
            cout<<"PROBLEM1"<<endl;
            assert(true==false);
        }
    }


    cout<<"Step4"<<endl;
    // start = chrono::high_resolution_clock::now(); 
    map<int,int> index_to_diamond_id = step_4(tetra_list,diamond_list,tetra_array,diamond_array,diamond_extra_bytes_array,
    array_size,anchor_dict,permutation_array,face_array);
    // cout<<10<<endl;
    // stop = chrono::high_resolution_clock::now(); 
    // duration = chrono::duration_cast<chrono::microseconds>(stop - start); 
    // cout<<"Time for creating the array : "<<duration.count()<<endl;
    
    // for (tuple<int,int,int> face : face_array)
    // {
    //     if (get<0>(face)==0 && get<1>(face)==0 && get<2>(face)==1)
    //     {
    //         cout<<"PROBLEM2"<<endl;
    //         assert(true==false);
    //     }
    // }

    time_to_access_ith_tetra(diamond_extra_bytes_array,array_size,tetra_list.size());
    time_to_access_ith_diamond(diamond_extra_bytes_array,array_size,diamond_list.size());
    time_to_compute_vertex_degree(diamond_array,diamond_extra_bytes_array,array_size,permutation_array,face_array,vertex_list.size());
    time_to_compute_BFS(diamond_array,diamond_extra_bytes_array,array_size,permutation_array,face_array,diamond_list.size());
    return 0;

    // cout<<face_array.size()<<" "<<permutation_array.size()<<endl;

    // for (int i=0;i<face_array.size();i++)
    // {
    //     cout<<get<0>(face_array[i])<<" "<<get<1>(face_array[i])<<" "<<get<2>(face_array[i])<<endl;
    //     cout<<get<0>(permutation_array[i])<<" "<<get<1>(permutation_array[i])<<" "<<get<2>(permutation_array[i])<<endl;
    // }

    // return 0;

    // map<tuple<int,int,int>,int> face_map;
    // for (tuple<int,int,int> face : face_array)
    // {
    //     face_map[face]++;
    // }
    // for (pair<tuple<int,int,int>,int> i : face_map)
    // {
    //     if (i.second>2 && get<0>(i.first)!=0 && get<1>(i.first)!=0 && get<2>(i.first)!=0)
    //     {
    //         cout<<"problem with "<<i.second<<" "<<get<0>(i.first)<<" "<<get<1>(i.first)<<" "<<get<2>(i.first)<<endl;
    //         assert(true==false);
    //     }
    // }

    // for (pair<tuple<int,int,int>,vector<Tetrahedron*>> i : face_dict)
    // {
    //     if (i.second.size()>2 && get<0>(i.first)!=0 && get<1>(i.first)!=0 && get<2>(i.first)!=0)
    //     {
    //         cout<<"problem with face "<<get<0>(i.first)<<" "<<get<1>(i.first)<<" "<<get<2>(i.first)<<endl;
    //         assert(true==false);
    //     }
    // }

    // for (Tetrahedron tetra : tetra_list)
    // {
    //     for (tuple<int,int,int> face : tetra.enumerate_faces())
    //     {
    //         if (face==tuple<int,int,int>{0,0,1})
    //         {
    //             cout<<"problem "<<tetra.get_id()<<endl;
    //             assert(true==false);
    //         }
    //     }
    // }


    // cout<<get<0>(face_array[3])<<" "<<get<1>(face_array[3])<<" "<<get<2>(face_array[3])<<endl;
    // cout<<get<0>(face_array[72182])<<" "<<get<1>(face_array[72182])<<" "<<get<2>(face_array[72182])<<endl;
    // cout<<get<0>(face_array[5426])<<" "<<get<1>(face_array[5426])<<" "<<get<2>(face_array[5426])<<endl;
    // cout<<endl;
    // check_2(diamond_array,array_size);
    // return 0;

    // double count=0;
    // int x=0;
    // double y=0;
    // vector<int> tmp_vector;
    // for (int i=0;i<array_size;i++)
    // {
    //     if (diamond_extra_bytes_array[i]==1)
    //     {
    //         x++;
    //     }
    //     if (diamond_array[i]!=-1)
    //     {
    //         tmp_vector.push_back(abs(diamond_array[i]-i));
    //         y++;
    //     }
    //     if (x==vertex_list.size())
    //     {
    //         break;
    //     }
    // }

    // write_in_csv(tmp_vector);    
    // cout<<"oui"<<endl;
    // check_4(diamond_list);
    cout<<10<<endl;
    // check_5(diamond_list);
    // return 0;


    cout<<"C'est parti"<<endl;
    // // int vertex = 89;
    // for (pair<int,vector<Tetrahedron*>> i : vertex_dict)
    // {
    //     int v=vertex_degree(diamond_list,i.first).size();
    //     if (v!=i.second.size())
    //     {
    //         cout<<v<<" "<<i.second.size()<<endl;
    //         cout<<i.first<<endl;
    //     }
    // }

    // vector<int> tetras_ids;
    // for (int i : vertex_degree(diamond_list,10))
    // {
    //     tetras_ids.push_back(i);
    //     tetra_list[i].display_vertices_id();
    // }
    // visualize_subset_tetra(vertex_list,tetra_list,tetras_ids);

    // display_face_diamond(diamond_extra_bytes_array,face_array,100);

    // for (tuple<int,int,int> face  : diamond_list[index_to_diamond_id[7903]].neighbours_faces)
    // {
    //     cout<<get<0>(face)<<" "<<get<1>(face)<<" "<<get<2>(face)<<endl;
    // }


    // unordered_set<int> v =vertex_degree(diamond_list,10);
    // cout<<"degree :"<<v.size()<<" "<<vertex_dict[10].size()<<endl;
    // cout<<"begin last step"<<endl;
    
    // cout<<"real degree : "<<vertex_dict[14].size()<<endl;
   


    // int v=vertex_degree_with_minimal_array(tetra_list,diamond_list,tetra_array,diamond_array,diamond_extra_bytes_array,
    // array_size,permutation_array,face_array,105);
    // cout<<"degree : "<<v<<endl;
   
    
    // cout<<"Time for creating the array : "<<duration.count()<<endl;

    double vertex_degree_time=0;
    double BFS_time=0;
    int count=0;


    // int v=vertex_degree_with_minimal_array(tetra_list,diamond_list,tetra_array,diamond_array,diamond_extra_bytes_array,
    //     array_size,permutation_array,face_array,105);

    // cout<<v<<" "<<vertex_dict[105].size()<<endl;
    // return 0;
    vector<int> cc;
    for (pair<int,vector<Tetrahedron*>> i : vertex_dict)
    {

        start = chrono::high_resolution_clock::now(); 
        int v=vertex_degree_with_minimal_array(diamond_array,diamond_extra_bytes_array,array_size,permutation_array,
        face_array,i.first);
        stop = chrono::high_resolution_clock::now(); 
        duration = chrono::duration_cast<chrono::microseconds>(stop - start); 
        cout<<"main1"<<endl;
        if (v!=i.second.size())
        {
            cout<<v<<" "<<i.second.size()<<endl;
            cout<<i.first<<endl;
            cc.push_back(i.first);
        }
        cout<<"main2"<<endl;
        vertex_degree_time+=duration.count();

        // start = chrono::high_resolution_clock::now(); 
        // vector<int> path= BFS(diamond_array,diamond_extra_bytes_array,array_size,index_to_diamond_id);
        // stop = chrono::high_resolution_clock::now(); 
        // duration = chrono::duration_cast<chrono::microseconds>(stop - start); 
        // BFS_time+=duration.count();

        // count++;
        // if (count==100)
        // {
        //     break;
        // }
    }
    cout<<"cc "<<cc.size()<<endl;
    cout<<"BFS time : "<<BFS_time/100<<endl;
    cout<<"Vertex degree time : "<<vertex_degree_time/100<<endl;

    // cout<<"Degree "<<vertex_degree(diamond_list,vertex)<<endl;
    // cout<<vertex_dict[102].size()<<endl;
    // auto start = chrono::high_resolution_clock::now(); 
    // vector<int> path= BFS(diamond_array,diamond_extra_bytes_array,array_size,index_to_diamond_id);
    // auto stop = chrono::high_resolution_clock::now(); 
    // auto duration = chrono::duration_cast<chrono::microseconds>(stop - start); 
    // cout<<"Time for BFS : "<<duration.count()<<endl;
    

    // for(Tetrahedron* tetra : vertex_dict[1])
    // {
    //     cout<<tetra->get_diamond_ref()->get_tetra_list().size()<<endl;
    // }

    // cout<<get<0>(edge_dict.begin()->first)<<" "<<get<1>(edge_dict.begin()->first)<<endl;
    // cout<<edge_dict[{0,7}].size()<<endl;
    // visualize_diamond(vertex_list,tetra_list,diamond_list,path,index_to_diamond_id);  
    // visualize_central_edges(vertex_list,diamond_list);
    cout<<"Compression size : "<<(float)array_size/tetra_list.size()<<endl;
    return 0;
}