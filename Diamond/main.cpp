#include <iostream> 
#include <tuple>
#include <array>
#include <vector>
#include <map>
#include "read_file.h"
#include "Vertex.h"
#include "Triangle.h"
#include "Tetrahedron.h"
#include "src.h"

using namespace std;



int main() 
{
    vector<Vertex> vertex_list;
    vector<Tetrahedron> tetra_list;

    tuple<vector<vector<double>>,vector<vector<double>>> result;
    // return both the geometry and the connectivity as a tuple
    result=read_file("hand.tet");

    // read the result tuple and encapsulate the geom. and connect. in propers classes
    preprocessing_tetra(result,vertex_list,tetra_list);

    cout<<"Vertex list size : "<<vertex_list.size()<<endl;
    cout<<"Tetrahedron list size : "<<tetra_list.size()<<endl;

    map<int,vector<Tetrahedron*>> vertex_dict;
    map<tuple<int,int>,vector<Tetrahedron*>> edge_dict;

    make_vertex_dict(tetra_list,vertex_dict);
    make_edge_dict(tetra_list,edge_dict);

    cout<<"Edges dict size : "<<edge_dict.size()<<endl;

    cout<<"Average Vertex Degree : "<<average_vertex_degree(vertex_dict)<<endl;
    cout<<"Average Edge Degree : "<<average_edge_degree(edge_dict)<<endl;
    cout<<"Edges per Vertex : "<<average_edges_per_vertex(vertex_list)<<endl;;

    // step_1(vertex_list,edge_dict);






    
    // vector<Vertex> vertex_list;
    // vector<Tetrahedron> tetra_list;

    // tuple<vector<vector<double>>,vector<vector<double>>> result;
    // // return both the geometry and the connectivity as a tuple
    // result=read_file("hand.tet");

    // // read the result tuple and encapsulate the geom. and connect. in propers classes
    // preprocessing_tetra(result,vertex_list,tetra_list);

    // cout<<"Vertex list size : "<<vertex_list.size()<<endl;
    // cout<<"Tetrahedron list size : "<<tetra_list.size()<<endl;

    // map<int,vector<Tetrahedron>> vertex_dict;
    // map<tuple<int,int>,vector<Tetrahedron>> edge_dict={};

    // make_vertex_dict(tetra_list,vertex_dict);
    // make_edge_dict(tetra_list,edge_dict);
    

    // cout<<"Average Vertex Degree : "<<average_vertex_degree(vertex_dict)<<endl;
    // cout<<"Average Edge Degree : "<<average_edge_degree(edge_dict)<<endl;
    // cout<<"Edges per Vertex : "<<average_edges_per_vertex(vertex_list)<<endl;;

    // step_1(vertex_list,edge_dict);





    // vector<int> max={};
    // for(pair<int,vector<Tetrahedron>> i : vertex_dict)
    // {
    //     max.push_back(i.second[0].get_id());
    // } 
    // cout<<*max_element(max.begin(),max.end())<<endl;


    // 

    // for(pair<tuple<int,int>,vector<Tetrahedron>> i : edge_dict)
    // {
    //     cout<<i.second[0].get_id()<<endl;
    // }
    // int count=0;
    // int count_tmp=0;
    // for (int i=0;i<tetra_list.size();i++)
    // {
    //     count_tmp=0;
    //     for (pair<tuple<int,int>,vector<Vertex *>> j : tetra_list[i].get_edges())
    //     {
    //         count_tmp+=j.second.size();
    //     }
    //     if (count_tmp>1)
    //     {
    //         count++;
    //     }
    // }
    // cout<<count<<endl;


        // vector<int> max;
    // for(int i=0;i<tetra_list.size();i++)
    // {
    //     max.push_back(tetra_list[i].get_vertices()[0]->get_id());
    //     for (int j=0;j<tetra_list[i].get_vertices().size();j++)
    //     {
    //         cout<<tetra_list[i].get_vertices()[j]->get_id()<<endl;
    //     }
    // }
    // cout<<*max_element(max.begin(),max.end())<<endl;

    return 0;
}  