#include "Tetrahedron.h"

using namespace std;

// Tetrahedron::Tetrahedron(int id,vector<Vertex>& vertex_list)
// {
//     this->id=id;

//     // add vertices
//     for(int i=0;i<vertex_list.size();i++)
//     {
//         Vertex& tmp=vertex_list[i];
//         this->vertices.push_back(tmp);
//     }
//     sort( this->vertices.begin( ), this->vertices.end( ), [ ]( Vertex& lhs, Vertex& rhs )
//     {
//     return lhs.get_id() < rhs.get_id();
//     });

//     // add edges
//     for(int i=0;i<this->vertices.size()-1;i++)
//     {
//         for(int j=i+1;j<this->vertices.size();j++)
//         {
//             vector<Vertex> tmp;
//             tuple<int,int> tmp_tuple=make_tuple(this->vertices[i].get_id(),this->vertices[j].get_id());
//             this->edges.insert(pair<tuple<int,int>,vector<Vertex>>(tmp_tuple,tmp));
//         }
//     }
// }

// void Tetrahedron::display_vertices_id()
// {
//     for(Vertex i : this->vertices)
//     {
//         cout<<i.get_id()<<" ";
//     }
//     cout<<endl;
// }

// vector<Tetrahedron>& Tetrahedron::get_neighbours()
// {
//     return this->neighbours;
// }

// int Tetrahedron::get_id()
// {
//     return this->id;
// }

// map<tuple<int,int>,vector<Vertex>>& Tetrahedron::get_edges()
// {
//     return this->edges;
// }

// vector<Vertex>& Tetrahedron::get_vertices()
// {
//     return this->vertices;
// }

// bool Tetrahedron::is_adjacent(Tetrahedron& tetra)
// {
//     int count=0;
//     for(int i=0;i<this->vertices.size();i++)
//     {
//         for(int j=0;j<tetra.get_vertices().size();j++)
//         {
//             if (this->vertices[i]==tetra.get_vertices()[j])
//             {
//                 count++;
//             }
//             if (count==2)
//             {
//                 return true;
//             }
//         }
//     }
//     return false;
// }

// void Tetrahedron::add_edge_vertex_match(tuple<int,int> key,Vertex& value)
// {
//     if (this->edges.count(key)==0)
//     {
//         cout<<"Error, key not in Tetra"<<endl;
//         cout<<get<0>(key)<<get<1>(key)<<endl;
//         cout<<"lala"<<endl;
//         cout<<this->vertices[0].get_id()<<endl;
//         // this->display_vertices_id();
//     }
//     else
//     {
//         this->edges.find(key)->second.push_back(value);
//     }
// }
Tetrahedron::Tetrahedron(int id,vector<Vertex*> vertex_list)
{
    this->id=id;
    for(int i=0;i<vertex_list.size();i++)
    {
        this->vertices.push_back(vertex_list[i]);
    }
    sort( this->vertices.begin( ), this->vertices.end( ), [ ]( Vertex* lhs, Vertex* rhs )
    {
    return lhs->get_id() < rhs->get_id();
    });
}

void Tetrahedron::display_vertices_id()
{
    for(Vertex* i : this->vertices)
    {
        cout<<i->get_id()<<" ";
    }
    cout<<endl;
}

vector<Tetrahedron*> Tetrahedron::get_neighbours()
{
    return this->neighbours;
}

int Tetrahedron::get_id()
{
    return this->id;
}

vector<Vertex*> Tetrahedron::get_vertices()
{
    return this->vertices;
}


// return edges id of a tetrahedron
vector<tuple<int,int>> Tetrahedron::enumerate_edges()
{
    int v0=this->vertices[0]->get_id();
    int v1=this->vertices[1]->get_id();
    int v2=this->vertices[2]->get_id();
    int v3=this->vertices[3]->get_id();

    tuple<int,int> e0 =make_tuple(v0,v1);
    tuple<int,int> e1 =make_tuple(v0,v2);
    tuple<int,int> e2 =make_tuple(v0,v3);
    tuple<int,int> e3 =make_tuple(v1,v2);
    tuple<int,int> e4 =make_tuple(v1,v3);
    tuple<int,int> e5 =make_tuple(v2,v3);
    
    vector<tuple<int,int>> edges={e0,e1,e2,e3,e4,e5};

    // for (tuple<int,int> i : edges)
    // {
    //     cout<<get<0>(i)<<" "<<get<1>(i)<<endl;
    // }

    return edges;
}

// bool Tetrahedron::is_adjacent(Tetrahedron* tetra)
// {
//     int count=0;
//     for(int i=0;i<this->vertices.size();i++)
//     {
//         for(int j=0;j<tetra.get_vertices().size();j++)
//         {
//             if (this->vertices[i]==tetra.get_vertices()[j])
//             {
//                 count++;
//             }
//             if (count==2)
//             {
//                 return true;
//             }
//         }
//     }
//     return false;
// }


