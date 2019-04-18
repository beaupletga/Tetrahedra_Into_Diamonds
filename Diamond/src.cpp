#include "src.h"

// // read a set of vertices and return all possible edges
// vector<tuple<int,int>> enumerate_edges(vector<Vertex>& vertices)
// {
//     vector<tuple<int,int>> edges;
//     for(int i=0;i<vertices.size()-1;i++)
//     {
//         for (int j=i+1;j<vertices.size();j++)
//         {
//             tuple<int,int> tmp=make_tuple(vertices[i].get_id(),vertices[j].get_id());
//             edges.push_back(tmp);
//         }
//     }
//     return edges;
// }

// // make a dict of <id of vertex,pointers towards tetra containing this vertex>
// void make_vertex_dict(vector<Tetrahedron> &tetra_list,map<int,vector<Tetrahedron>> &vertex_dict)
// {
//     // std::map<int,vector<Tetrahedron*>> vertex_dict;
//     // iterate over the triangles and add the 3 edges into edge_dict
//     for(int i=0;i<tetra_list.size();i++)
//     {
//         for (Vertex j : tetra_list[i].get_vertices())
//         {
//             // cout<<j->get_id()<<endl;
//             if(vertex_dict.count(j.get_id())==0)
//             {
//                 Tetrahedron& lalala=tetra_list[i];
//                 vector<Tetrahedron> tmp={lalala};
//                 vertex_dict.insert({j.get_id(),tmp});
//             }
//             else
//             {
//                 Tetrahedron& lalala=tetra_list[i];
//                 vertex_dict.find(j.get_id())->second.push_back(lalala);
//             }
//         }
//     }

//     vector<int> max={};
//     for(pair<int,vector<Tetrahedron>> i : vertex_dict)
//     {
//         max.push_back(i.second[0].get_id());
//     } 
//     cout<<*max_element(max.begin(),max.end())<<endl;
//     // return vertex_dict;
// }

// // make a dict of <edge,pointers towards tetra containing this edge>
// // where edge is a tuple <id of vertex,id of vertex> which are both int
// void make_edge_dict(vector<Tetrahedron>& tetra_list,map<tuple<int,int>,vector<Tetrahedron>> &edge_dict)
// {
//     // each edge is a tuple of vertice and belong to at least 1 tetra
//     // std::map<tuple<int,int>,vector<Tetrahedron *>> edge_dict;
//     // iterate over the triangles and add the 3 edges into edge_dict
//     for(int i=0;i<tetra_list.size();i++)
//     {
//         for (tuple<int,int> j : enumerate_edges(tetra_list[i].get_vertices()))
//         {
//             if(edge_dict.count(j)==0)
//             {
//                 Tetrahedron& lalala=tetra_list[i];
//                 vector<Tetrahedron> tmp={lalala};
//                 edge_dict.insert({j,tmp});
//                 // if (edge_dict.find(j)->second.back()->get_id()>125127)
//                 // {
//                 //     cout<<"Error: "<<edge_dict.find(j)->second.back()->get_id()<<endl;
//                 // }
//             }
//             else
//             {
//                 Tetrahedron& lalala=tetra_list[i];
//                 edge_dict.find(j)->second.push_back(lalala);
//                 // if (edge_dict.find(j)->second.back()->get_id()>125127)
//                 // {
//                 //     cout<<"Error: "<<edge_dict.find(j)->second.back()->get_id()<<endl;
//                 // }
//             }
//         }
//     }
//     // return edge_dict;
// }

// // // add references to the neighboring edges
// // // index : to which vertex do we have to add neighbours
// // // vertex_list : vertex list in a tetrahedra
// // void add_neighours(int index,vector<Vertex>& vertex_list)
// // {
// //     for(int i=0;i<vertex_list.size();i++)
// //     {
// //         if (i!=index)
// //         {
// //             vertex_list[index].add_neighbours(vertex_list);
// //         }
// //     }
// // }


// // vertex_list and tetra_list are empty
// // read result which is a tuple containing both the geometry and connectivity
// // encapsulate both into proper classes
// void preprocessing_tetra(tuple<vector<vector<double>>,vector<vector<double>>>& result, vector<Vertex>& vertex_list, vector<Tetrahedron>& tetra_list)
// {
//     vector<vector<double>> geometry = get<0>(result);
//     vector<vector<double>> connectivity = get<1>(result);

//     for(int i=0;i<geometry.size();i++)
//     {
//         Vertex tmp=Vertex(i,geometry[i]);
//         vertex_list.push_back(tmp);
//     }

//     for(int i=0;i<connectivity.size();i++)
//     {
//         Vertex& v0=vertex_list[connectivity[i][0]];
//         Vertex& v1=vertex_list[connectivity[i][1]];
//         Vertex& v2=vertex_list[connectivity[i][2]];
//         Vertex& v3=vertex_list[connectivity[i][3]];

//         vector<Vertex> tmp0 ={v0,v1,v2,v3};
//         Tetrahedron tmp1=Tetrahedron(i,tmp0);
//         tetra_list.push_back(tmp1);
//         v0.add_neighbours(tmp0);
//         v1.add_neighbours(tmp0);
//         v2.add_neighbours(tmp0);
//         v3.add_neighbours(tmp0);
//         // add_neighours(0,tmp0);
//         // add_neighours(1,tmp0);
//         // add_neighours(2,tmp0);
//         // add_neighours(3,tmp0);
//     }
// }   

// // in average, how many tetra are adjacents to a vertex
// double average_vertex_degree(std::map<int,vector<Tetrahedron>>& vertex_dict)
// {
//     double count=0;

//     for (std::pair<int, vector<Tetrahedron>> element : vertex_dict) 
//     {		
//         count+=element.second.size();
// 	}
//     return count/vertex_dict.size();
// }

// // in average, how many tetra are adjacents to a vertex
// double average_edge_degree(std::map<tuple<int,int>,vector<Tetrahedron>>& edge_dict)
// {
//     double count=0;

//     for (std::pair<tuple<int,int>, vector<Tetrahedron>> element : edge_dict) 
//     {		
//         count+=element.second.size();
// 	}
//     return count/edge_dict.size();
// }

// // how many edges per vertex
// double average_edges_per_vertex(vector<Vertex>& vertex_list)
// {
//     double count=0;

//     for (Vertex element : vertex_list) 
//     {		
//         count+=element.get_neighbours().size();
// 	}
//     return count/vertex_list.size();
// }

// Vertex& pick_random_edge(Vertex& vertex)
// {
//     int vertex_index =rand() % vertex.get_neighbours().size();
//     return vertex.get_neighbours()[vertex_index];
// }

// void step_1(vector<Vertex>& vertex_list,map<tuple<int,int>,vector<Tetrahedron>>& edge_to_tetra)
// {
//     map<tuple<int,int>,vector<Vertex>> edge_to_vertex;
//     for(int i=0;i<vertex_list.size();i++)
//     {
//         Vertex v2 =pick_random_edge(vertex_list[i]);
//         tuple<int,int> tmp;
//         if (vertex_list[i].get_id()<v2.get_id())
//         {
//             tmp= make_tuple(vertex_list[i].get_id(),v2.get_id());
//         }
//         else
//         {
//             tmp= make_tuple(v2.get_id(),vertex_list[i].get_id());
//         }
//         if (edge_to_vertex.count(tmp)==0)
//         {
//             Vertex& vert_tmp=vertex_list[i];
//             vector<Vertex> vec_tmp={vert_tmp};
//             edge_to_vertex.insert(pair<tuple<int,int>,vector<Vertex>>(tmp,vec_tmp));
//         }
//         else
//         {
//             Vertex& vert_tmp=vertex_list[i];
//             edge_to_vertex.find(tmp)->second.push_back(vert_tmp);
//         }
//     }
//     int count=0;

//     cout<<edge_to_tetra.size()<<endl;
//     // for(pair<tuple<int,int>,vector<Tetrahedron *>> i : edge_to_tetra)
//     // {
//     //     cout<<i.second[0]->get_id()<<endl;
//     // }


//     // for (pair<tuple<int,int>,vector<Vertex *>> i : edge_to_vertex)
//     // {
//     //     vector<Tetrahedron *> tetra_tmp= edge_to_tetra.find(i.first)->second;
//     //     cout<<tetra_tmp[0]->get_id()<<endl;
//     //     for (Tetrahedron * j:tetra_tmp)
//     //     {
//     //         // j->add_edge_vertex_match(i.first,i.second[0]);
//     //         // count++;
//     //         // j->get_vertices().size();
//     //     }
//     // }
// }



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
                vertex_dict.insert(std::pair<int,vector<Tetrahedron*>>(j->get_id(),tmp));
            }
            else
            {
                vertex_dict.find(j->get_id())->second.push_back(&tetra_list[i]);
            }
        }
    }

    // vector<int> max;
    // for (pair<int,vector<Tetrahedron*>> i : vertex_dict)
    // {
    //     for(int j=0;j<i.second.size();j++)
    //     {
    //         max.push_back(i.second[j]->get_id());
    //     }
    //     // cout<<i.second[0]->get_id()<<endl;
    // }
    // cout<<*max_element(max.begin(),max.end())<<endl;
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
                edge_dict.insert(pair<tuple<int,int>,vector<Tetrahedron *>>(edges[j],tmp));
            }
            else
            {
                edge_dict.find(edges[j])->second.push_back(&tetra_list[i]);
            }
            // cout<<endl;
        }
    }
    // vector<int> max;
    // for (pair<tuple<int,int>,vector<Tetrahedron*>> i : edge_dict)
    // {
    //     for(int j=0;j<i.second.size();j++)
    //     {
    //         max.push_back(i.second[j]->get_id());
    //     }
    //     // cout<<i.second[0]->get_id()<<endl;
    // }
    // cout<<*max_element(max.begin(),max.end())<<endl;
}

// add references to the neighboring edges
// index : to which vertex do we have to add neighbours
// vertex_list : vertex list in a tetrahedra
// void add_neighours(int index,vector<Vertex *> vertex_list)
// {
//     vector<Vertex *> neighbours;
//     for(int i=0;i<vertex_list.size();i++)
//     {
//         if (i!=index)
//         {
//             neighbours.push_back(vertex_list[i]);
//             vertex_list[index]->add_neighbours(neighbours);
//         }
//     }
// }


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

// in average, how many tetra are adjacents to a vertex
double average_vertex_degree(std::map<int,vector<Tetrahedron*>>& vertex_dict)
{
    double count=0;

    for (std::pair<int, vector<Tetrahedron*>> element : vertex_dict) 
    {		
        count+=element.second.size();
	}
    return count/vertex_dict.size();
}

// in average, how many tetra are adjacents to a vertex
double average_edge_degree(std::map<tuple<int,int>,vector<Tetrahedron *>> edge_dict)
{
    double count=0;

    for (std::pair<tuple<int,int>, vector<Tetrahedron *>> element : edge_dict) 
    {		
        count+=element.second.size();
	}
    return count/edge_dict.size();
}

// how many edges per vertex
double average_edges_per_vertex(vector<Vertex> vertex_list)
{
    double count=0;

    for (Vertex element : vertex_list) 
    {		
        count+=element.get_neighbours().size();
	}
    return count/vertex_list.size();
}

Vertex* pick_random_edge(Vertex& vertex)
{
    int vertex_index =rand() % vertex.get_neighbours().size();
    return vertex.get_neighbours()[vertex_index];
}


void step_1(vector<Vertex>& vertex_list,map<tuple<int,int>,vector<Tetrahedron*>>& edge_to_tetra)
{
    map<tuple<int,int>,vector<Vertex*>> edge_to_vertex;
    for(int i=0;i<vertex_list.size();i++)
    {
        Vertex* v2 =pick_random_edge(vertex_list[i]);
        tuple<int,int> tmp;
        if (vertex_list[i].get_id()<v2->get_id())
        {
            tmp= make_tuple(vertex_list[i].get_id(),v2->get_id());
        }
        else
        {
            tmp= make_tuple(v2->get_id(),vertex_list[i].get_id());
        }
        if (edge_to_vertex.count(tmp)==0)
        {
            vector<Vertex*> vec_tmp={&vertex_list[i]};
            edge_to_vertex.insert({tmp,vec_tmp});
        }
        else
        {
            edge_to_vertex.find(tmp)->second.push_back(&vertex_list[i]);
        }
    }

    double count_failure=0;
    for (pair<tuple<int,int>,vector<Vertex*>> i : edge_to_vertex)
    {
        // for (int j=0;j<i.second.size();j++)
        // {
        //     cout<<i.second[j]->get_id()<<endl;
        // }
        if (i.second.size()>1)
        {
            count_failure++;
        }
    }
    cout<<count_failure/edge_to_vertex.size()<<endl;

}


    





