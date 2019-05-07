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


bool close_to_border(map<tuple<int,int>,vector<Tetrahedron*>> &edge_dict,tuple<int,int> &edge)
{
    for(Tetrahedron* tetra : edge_dict[edge])
    {
        if (tetra->get_is_on_boundary())
        {
            return true;
        }
    }
    return false;
}




double fitness(vector<Tetrahedron> &tetra_list,map<tuple<int,int>,int> &edge_list,map<tuple<int,int>,vector<Tetrahedron*>> &edge_dict)
{
    double fitness_value=0;
    double count_edge_in_tetra;
    for (Tetrahedron &tetra : tetra_list)
    {
        count_edge_in_tetra=0;
        for (tuple<int,int> edge : tetra.enumerate_edges())
        {
            if (edge_list.count(edge)>0 && edge_list[edge]==1)
            {
                count_edge_in_tetra++;
            }
        }
        if (count_edge_in_tetra==1)
        {
            fitness_value++;
        }
    }
    return fitness_value/tetra_list.size();
}

double fitness_quick(vector<Tetrahedron> &tetra_list,map<tuple<int,int>,int> &edge_list,map<tuple<int,int>,vector<Tetrahedron*>> &edge_dict,tuple<int,int> &edge_changed)
{
    double fitness_value=0;
    if (edge_list[edge_changed]==1)
    {   
        for(Tetrahedron* tetra : edge_dict[edge_changed])
        {
            double conflict=0;
            for(tuple<int,int> edge : tetra->enumerate_edges())
            {
                if (edge_list[edge]==1)
                {
                    conflict++;
                }
            }
            if (conflict==1)
            {
                fitness_value++;
            }
            else
            {
                fitness_value--;
            }
        }
    }
    else if (edge_list[edge_changed]==0)
    {   
        for(Tetrahedron* tetra : edge_dict[edge_changed])
        {
            double conflict=0;
            for(tuple<int,int> edge : tetra->enumerate_edges())
            {
                if (edge_list[edge]==1)
                {
                    conflict++;
                    break;
                }
            }
            if (conflict==0)
            {
                fitness_value--;
            }
            else
            {
                fitness_value++;
            }
        }
    }
    return fitness_value;
}





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


    // cout<<"lala"<<endl;

    for (Vertex &i : vertex_list)
    {
        i.sort_neighbours();
    }

    cout<<"Vertex list size : "<<vertex_list.size()<<endl;
    cout<<"Tetrahedron list size : "<<tetra_list.size()<<endl;

    map<int,vector<Tetrahedron*>> vertex_dict;
    map<tuple<int,int>,vector<Tetrahedron*>> edge_dict;
    map<tuple<int,int,int>,vector<Tetrahedron*>> face_dict;

    make_vertex_dict(tetra_list,vertex_dict);
    make_edge_dict(tetra_list,edge_dict);
    make_face_dict(tetra_list ,face_dict);

    for(pair<tuple<int,int,int>,vector<Tetrahedron*>> face :face_dict)
    {
        for(int i=0;i<face.second.size()-1;i++)
        {
            for(int j=i+1;j<face.second.size();j++)
            {
                face.second[i]->add_neighbour(face.second[j]);
                face.second[j]->add_neighbour(face.second[i]);
            }
        }
    }


    double count_face=0;
    for (Tetrahedron i : tetra_list)
    {
        count_face+=i.get_is_on_boundary();
    }
    cout<<"Share of Tetrahedron on the boundary : "<<count_face/tetra_list.size()<<endl;

    cout<<"Edges dict size : "<<edge_dict.size()<<endl;

    cout<<"Average Vertex Degree : "<<average_vertex_degree(vertex_dict)<<endl;
    cout<<"Average Edge Degree : "<<average_edge_degree(edge_dict)<<endl;
    cout<<"Edges per Vertex : "<<average_edges_per_vertex(vertex_list)<<endl;;

    map<tuple<int,int>,vector<Vertex*>> edge_to_vertex;

    // for(Tetrahedron tetra : tetra_list)
    // {
    //     if (tetra.get_is_on_boundary())
    //     {
    //         vector<tuple<int,int,int>> ocurrences;
    //         for(tuple<int,int> edge : tetra.enumerate_edges())
    //         {
    //             if(is_cycle(edge_dict[edge]))
    //             {
    //                 if (count_if(edge_dict[edge].begin(),edge_dict[edge].end(),[](Tetrahedron* i){return i->get_in_diamond();})==0)
    //                 {
    //                     // int tmp=count_if(edge_dict[edge].begin(),edge_dict[edge].end(),[](Tetrahedron* i){return i->get_is_on_boundary();});
    //                     ocurrences.push_back({get<0>(edge),get<1>(edge),edge_dict[edge].size()});
    //                     // for (Tetrahedron* tmp : edge_dict[edge])
    //                     // {
    //                     //     tmp->set_in_diamond(true);
    //                     // }
    //                 }
    //             }
    //         }
    //         if (ocurrences.size()>0)
    //         {
    //             tuple<int,int,int> max = *max_element( ocurrences.begin(), ocurrences.end(),
    //                          []( tuple<int,int,int> &a, tuple<int,int,int> &b )
    //                          {
    //                              return get<2>(a) < get<2>(b);
    //                          } );
    //             tuple<int,int> edge={get<0>(max),get<1>(max)};
    //             // diamond_list[edge]=edge_dict[edge];
    //             // and mark all the tetra of this new diamond
    //             for (Tetrahedron* tmp : edge_dict[edge])
    //             {
    //                 tmp->set_in_diamond(true);
    //             }
    //         }
    //     }
    // }

    // edge_to_vertex=step_1_bfs(vertex_list,tetra_list,edge_dict);

    // map<tuple<int,int>,int> edge_list;

    // for (pair<tuple<int,int>,vector<Tetrahedron*>> edge : edge_dict)
    // {
    //     if (is_cycle(edge.second))// && close_to_border(edge_dict,edge.first))
    //     {
    //         // if (rand()%100<10)
    //         if (edge_to_vertex.count(edge.first)>0)
    //         {
    //             edge_list[edge.first]=1;
    //         }
    //         else
    //         {
    //             edge_list[edge.first]=0;
    //         }
    //     }
    // }

    // double before_fitness,new_fitness;
    
    // int iter=10000;
    // double t=1/iter;
    // for (int i=0;i<iter;i++)
    // {
    //     auto it = edge_list.begin();
    //     std::advance(it, rand() % edge_list.size());
    //     tuple<int,int> random_key = it->first;
    //     edge_list[random_key]=1-edge_list[random_key];
    //     // new_fitness=fitness(tetra_list,edge_list,edge_dict);
    //     new_fitness=fitness_quick(tetra_list,edge_list,edge_dict,random_key);
    //     double random=(double)(rand()%1000)/1000;
    //     if (new_fitness<0)
    //     {
    //         // if (random>exp((new_fitness-before_fitness)/t))
    //         {
    //             edge_list[random_key]=1-edge_list[random_key];
    //         }
    //     }
    //     t+=1/iter;   
    //     // if (i%10000==0)
    //     // {
    //     //     cout<<new_fitness<<endl;
    //     // }
    // }
    // before_fitness=fitness(tetra_list,edge_list,edge_dict);
    // cout<<"Fitness : "<<before_fitness<<endl;
    // cout<<"Fitness : "<<new_fitness<<endl;

    // for (pair<tuple<int,int>,vector<Tetrahedron*>> edge : edge_dict)
    // {
    //     for_each(edge.second.begin(),edge.second.end(),[](Tetrahedron* i){i->set_in_diamond(false);});
    // }

    // for (pair<tuple<int,int>,vector<Tetrahedron*>> edge : edge_dict)
    // {
    //     if (edge_list.count(edge.first)>0 && edge_list[edge.first]==1)
    //     {
    //         // for_each(edge.second.begin(),edge.second.end(),[](Tetrahedron* i){i->set_in_diamond(true);});
    //         for (Tetrahedron* i : edge.second)
    //         {
    //             i->set_in_diamond(true);
    //         }
    //     }
    // }
    
    // for (int i=0;i<10000;i++)
    // {
    //     for (Tetrahedron &tetra : tetra_list)
    //     {
    //         tetra.set_in_diamond(false);
    //     }
    //     edge_to_vertex=step_1_bfs(vertex_list,tetra_list,edge_dict);
    //     // double count_tetra_diamond=0;
    //     // for (int i=0;i<tetra_list.size();i++)
    //     // {
    //     //     count_tetra_diamond+=tetra_list[i].get_in_diamond();
    //     // }
    //     // if (count_tetra_diamond/tetra_list.size()>0.78)
    //     {
    //         // outfile<<<<count_tetra_diamond/tetra_list.size()<<endl;
    //         // stats(edge_to_vertex,tetra_list);
    //         // cout<<endl;
    //     }
        
    // }
    edge_to_vertex=step_1_bfs(vertex_list,tetra_list,edge_dict);
    // edge_to_vertex=step_1_edge_degree(vertex_list,tetra_list,edge_dict);
    // edge_to_vertex=step_1_vertex_choose_neighbour(vertex_list,tetra_list,edge_dict);
    

    // this method doesn't work if you use step_1_vertex_choose_neighbour because all diamond are not cycles
    // step_2(edge_to_vertex,tetra_list,edge_dict);

    // for (pair<tuple<int,int>,vector<Tetrahedron*>> i : edge_dict)
    // {
    //     if (rand()%100<23 && is_cycle(i.second))
    //     {
    //         bool already_in=false;
    //         for (Tetrahedron* tetra : i.second)
    //         {
    //             if (tetra->get_in_diamond()==true)
    //             {
    //                 already_in=true;
    //                 break;
    //             }
    //         }
    //         if (!already_in)
    //         {
    //             for (Tetrahedron* tetra : i.second)
    //             {
    //                 tetra->set_in_diamond(true);
    //             }
    //             edge_to_vertex[i.first]={&vertex_list[get<0>(i.first)]};
    //         }
    //     }
        
    // }


    stats(edge_to_vertex,tetra_list);

    visualize_diamond_isolated(vertex_list,tetra_list,edge_dict,edge_to_vertex);
    // visualize(tetra_list);

    return 0;
}  