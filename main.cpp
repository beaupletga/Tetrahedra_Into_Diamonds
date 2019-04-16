#include <iostream> 
#include <tuple>
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

    cout<<"Vertex list size "<<vertex_list.size()<<endl;
    cout<<"Tetrahedron list size "<<tetra_list.size()<<endl;

    std::map<int,vector<Tetrahedron *>> vertex_dict;
    std::map<tuple<int,int>,vector<Tetrahedron *>> edge_dict;

    vertex_dict=make_vertex_dict(tetra_list);
    edge_dict=make_edge_dict( tetra_list);
    
    return 0;
}