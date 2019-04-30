#include <iostream> 
#include <tuple>
#include <array>
#include <vector>
#include <map>

#include "read_file.h"
#include "Vertex.h"
#include "Triangle.h"
#include "Tetrahedron.h"
#include "preprocessing.h"
#include "stats.h"
#include "step1.h"
#include "step2.h"

using namespace std;

int score(vector<Tetrahedron*> list)
{
    int a=0;
    for (Tetrahedron* i : list)
    {
        a+=i->get_in_diamond();
    }
    if (a==0)
    {
        return -list.size();
    }
    return a;
}

// decreasing
bool cmp(pair<tuple<int,int>,vector<Tetrahedron*>> lhs, pair<tuple<int,int>,vector<Tetrahedron*>> rhs)
{
    // return lhs.second.size() < rhs.second.size();
    return score(lhs.second)<score(rhs.second);
}


void greedy(map<tuple<int,int>,vector<Tetrahedron*>>& edge_dict)
{
    pair<tuple<int,int>,vector<Tetrahedron*>> tmp;
    // for (int i=0;i<10;i++)
    int count=0;
    do
    {
        tmp= *min_element(edge_dict.begin(),edge_dict.end(),cmp);
        // cout<<get<0>(tmp.first)<<","<<get<1>(tmp.first)<<endl;
        // cout<<score(tmp.second)<<endl;
        // cout<<endl;
        for (Tetrahedron* tetra : tmp.second)
        {
            tetra->set_in_diamond(true);
        }
        count++;
        if (count%1000==0)
        {
            cout<<count<<endl;
        }
    }while (score(tmp.second)>=0);
    // for (Tetrahedron i : tetra_list)
    // {

    // }

}




int main() 
{
    vector<Vertex> vertex_list;
    vector<Tetrahedron> tetra_list;

    tuple<vector<vector<double>>,vector<vector<double>>> result;
    // return both the geometry and the connectivity as a tuple
    result=read_file("cow.tet");

    // read the result tuple and encapsulate the geom. and connect. in propers classes
    preprocessing_tetra(result,vertex_list,tetra_list);

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
    edge_to_vertex=step_1_bfs(vertex_list,tetra_list,edge_dict);

    // step_2(edge_to_vertex,tetra_list,edge_dict);

    // stats(edge_to_vertex,tetra_list);

    // double count_tetra_diamond=0;
    // for (int i=0;i<tetra_list.size();i++)
    // {
    //     count_tetra_diamond+=tetra_list[i].get_in_diamond();
    // }
    // cout<<"Share of tetra in full diamond : "<<count_tetra_diamond/tetra_list.size()<<endl;

    return 0;
}  