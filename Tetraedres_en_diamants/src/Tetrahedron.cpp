#include "../include/Tetrahedron.h"

Tetrahedron::Tetrahedron(int id,vector<Vertex*> vertex_list)
{
    this->id=id;
    this->in_diamond=false;
    this->is_on_boundary=false;
    for(int i=0;i<vertex_list.size();i++)
    {
        this->vertices.push_back(vertex_list[i]);
    }
    sort( this->vertices.begin( ), this->vertices.end( ), [ ]( Vertex* lhs, Vertex* rhs )
    {
    return lhs->get_id() < rhs->get_id();
    });
    this->edges=this->enumerate_edges();
}

void Tetrahedron::display_vertices_id()
{
    for(Vertex* i : this->vertices)
    {
        cout<<i->get_id()<<" ";
    }
    cout<<endl;
}

void Tetrahedron::display_edges()
{
    for(tuple<int,int> i : this->edges)
    {
        cout<<"("<<get<0>(i)<<","<<get<1>(i)<<")"<<" ";
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

    return edges;
}

// return faces of a tetrahedron
vector<tuple<int,int,int>> Tetrahedron::enumerate_faces()
{
    int v0=this->vertices[0]->get_id();
    int v1=this->vertices[1]->get_id();
    int v2=this->vertices[2]->get_id();
    int v3=this->vertices[3]->get_id();

    tuple<int,int,int> f0 =make_tuple(v0,v1,v2);
    tuple<int,int,int> f1 =make_tuple(v0,v2,v3);
    tuple<int,int,int> f2 =make_tuple(v1,v2,v3);
    tuple<int,int,int> f3 =make_tuple(v0,v1,v3);
    
    vector<tuple<int,int,int>> faces={f0,f1,f2,f3};

    return faces;
}

// 2 tetra are adjacents if they share 3 vertices
// check if 2 tetra are adjacents
bool Tetrahedron::is_adjacent(Tetrahedron* tetra)
{
    int count=0;
    for(int i=0;i<this->vertices.size();i++)
    {
        for(int j=0;j<tetra->get_vertices().size();j++)
        {
            if (this->vertices[i]==tetra->get_vertices()[j])
            {
                count++;
            }
            if (count>=3)
            {
                return true;
            }
        }
    }
    return false;
}


void Tetrahedron::set_in_diamond(bool value)
{
    this->in_diamond=value;
}

bool Tetrahedron::get_in_diamond()
{
    return this->in_diamond;
}

void Tetrahedron::set_is_on_boundary(bool value)
{
    this->is_on_boundary=value;
}
bool Tetrahedron::get_is_on_boundary()
{
    return this->is_on_boundary;
}

void Tetrahedron::add_neighbour(Tetrahedron* tetra)
{
    this->neighbours.push_back(tetra);
}

tuple<double,double,double> Tetrahedron::get_barycenter()
{
    double x=0;
    double y=0;
    double z=0;
    for(Vertex* vertex : this->get_vertices())
    {
        x+=vertex->get_coords()[0];
        y+=vertex->get_coords()[1];
        z+=vertex->get_coords()[2];
    }
    tuple<double,double,double> tmp = {x/4,y/4,z/4};
    return tmp;
}

Diamond* Tetrahedron::get_diamond_ref()
{
    return this->diamond_ref;
}

int Tetrahedron::get_position_in_diamond()
{
    return this->position_in_diamond;
}

void Tetrahedron::set_diamond_ref(Diamond* diamond)
{
    this->diamond_ref=diamond;
}

void Tetrahedron::set_position_in_diamond(int position)
{
    this->position_in_diamond=position;
}

tuple<int,int,int> Tetrahedron::get_opposite_face(Vertex* vertex)
{
    for (tuple<int,int,int> face : this->enumerate_faces())
    {
        if (vertex->get_id()!=get<0>(face) && vertex->get_id()!=get<1>(face) && vertex->get_id()!=get<2>(face))
        {
            return face;
        }
    }
    // a vertex can't belong to all face of a tetrahedron
    assert(true==false);
}



