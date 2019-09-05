#include "../include/Diamond.h"


Diamond::Diamond()
{
    
}


// constructor for each diamond
// we know that the set of tetra shape is a cycle
Diamond::Diamond(int id,vector<Tetrahedron*>& elements,Vertex* anchor_vertex,bool has_anchor)
{
    this->id=id;
    this->has_anchor=has_anchor;
    bool already_in=false;
    this->tetra_list.push_back(elements[0]);
    this->anchor_vertex=anchor_vertex;

    // we are in an isolated tetra
    if (elements.size()==1)
    {
        this->neighbours={NULL,NULL,NULL,NULL};
        this->neighbours_faces={{0,0,0},{0,0,0},{0,0,0},{0,0,0}};
        this->permutation = {{0,0,0},{0,0,0},{0,0,0},{0,0,0}};
        if (this->has_anchor)
        {
            // the first face must be the one opposite to the anchor
            tuple<int,int,int> opposite_anchor_face=elements[0]->get_opposite_face(anchor_vertex);
            this->neighbours_faces[0]=opposite_anchor_face;
            this->vertex_order.push_back(anchor_vertex->get_id());
            int x=1;

            // we add the other face arbitrarily
            for(int i=0;i<4;i++)
            {
                if (elements[0]->get_vertices()[i]->get_id()!=anchor_vertex->get_id())
                {
                    this->neighbours_faces[x]=elements[0]->get_opposite_face(elements[0]->get_vertices()[i]);
                    this->vertex_order.push_back(elements[0]->get_vertices()[i]->get_id());
                    x++;
                }
            }
        }
        // if the isolated tetra is not anchored, then we add the faces arbitrarily
        else
        {
            for (int i=0;i<4;i++)
            {
                this->neighbours_faces[i]=elements[0]->get_opposite_face(elements[0]->get_vertices()[i]);
                this->vertex_order.push_back(elements[0]->get_vertices()[i]->get_id());

            }
        }
        
    }
    else
    {
        for(int i=0;i<elements.size()*2;i++)
        {
            this->neighbours.push_back(NULL);
            this->neighbours_faces.push_back({0,0,0});
            this->permutation.push_back({0,0,0});
        }
    }
    // we want to add the tetra such that the order is the same as in the cycle around the central edge
   
    while (this->tetra_list.size()!=elements.size())
    {
        for(int i=0;i<elements.size();i++)
        {
            already_in=false;
            // if the new element is adjacent to the last added one
            if (elements[i]->is_adjacent(this->tetra_list.back()))
            {
                // we check that this new element isn't already added
                for (int j=0;j<this->tetra_list.size();j++)
                {
                    if (this->tetra_list[j]->get_id()==elements[i]->get_id())
                    {
                        already_in=true;
                        break;
                    }
                }
                // if it's not already added, then we add it
                if (!already_in)
                {
                    this->tetra_list.push_back(elements[i]);
                    // elements[i]->display_vertices_id();
                    // cout<<elements[i]->get_id()<<endl;
                    break;
                }
            }
        }
    }
}

unordered_set<int> Diamond::get_vertices_id()
{
    unordered_set<int> ids;
    for (Tetrahedron* tetra : this->tetra_list)
    {
        for (Vertex* vertex : tetra->get_vertices())
        {
            ids.insert(vertex->get_id());
        }
    }
    return ids;
}


int Diamond::get_id()
{
    return this->id;
}

vector<Tetrahedron*> Diamond::get_tetra_list()
{
    return this->tetra_list;
}

vector<Diamond*> Diamond::get_neighbours()
{
    return this->neighbours;
}

Vertex* Diamond::get_anchor_vertex()
{
    return this->anchor_vertex;
}

pair<int,int> Diamond::get_central_edge()
{   
    return this->central_edge;
}

void Diamond::set_permutation(vector<int> &permutation,int i)
{
    this->permutation[i]=permutation;
}

vector<int> Diamond::get_permutation(int i)
{
    if (i>this->permutation.size())
    {
        cout<<"Size limit exceeded"<<endl;
        assert(true==false);
    }
    return this->permutation[i];
}
bool Diamond::get_has_anchor()
{
    return this->has_anchor;
}
void Diamond::set_has_anchor(bool has_anchor)
{
    this->has_anchor=has_anchor;
}

// return the external faces of a diamond (there is 2*number_of_tetra_in_diamond)
vector<tuple<int,int,int>> Diamond::get_external_faces()
{
    map<tuple<int,int,int>,int> faces;
    vector<tuple<int,int,int>> external_faces;
    // put faces in dictionary
    for (Tetrahedron* tetra : this->tetra_list)
    {
        for (tuple<int,int,int> face : tetra->enumerate_faces())
        {
            faces[face]++;
        }
    }
    // gather all faces appearing only once
    for(pair<tuple<int,int,int>,int> face : faces)
    {
        if (face.second==1)
        {
            // cout<<get<0>(face.first)<<" "<<get<1>(face.first)<<" "<<get<2>(face.first)<<endl;
            external_faces.push_back(face.first);
        }
    }
    return external_faces;
}

// take a face of the diamond and a reference toward another diamond and add this neighbour to the diamond
void Diamond::add_neighbour(tuple<int,int,int> &face,Diamond* neighbour)
{
    if (this->tetra_list.size()>1)
    {
        // we want to know which tetra has this face
        for (int i=0;i<this->tetra_list.size();i++)
        {
            int similarity=0;
            // cout<<this->tetra_list.size()<<endl;
            // tetra_list[0]->display_vertices_id();
            for (Vertex* vertex : this->tetra_list[i]->get_vertices())
            {
                if (vertex->get_id()==get<0>(face) || vertex->get_id()==get<1>(face) || vertex->get_id()==get<2>(face))
                {
                    similarity++;
                }
            }
            // if a tetra shared 3 vertices with the face then the face belong to it
            if (similarity==3)
            {
                if (get<0>(face)==this->anchor_vertex->get_id() || get<1>(face)==this->anchor_vertex->get_id()
                || get<2>(face)==this->anchor_vertex->get_id())
                {
                    this->neighbours[2*i]=neighbour;
                    this->neighbours_faces[2*i]=face;
                }
                else
                {
                    this->neighbours[2*i+1]=neighbour;
                    this->neighbours_faces[2*i+1]=face;
                }
                break;
            }
        }
    }
    
    else
    {
        for (int i=0;i<4;i++)
        {
            if (this->neighbours_faces[i]==face)
            {
                this->neighbours[i]=neighbour;
            }
        }       
    }
}

// take the reference of a diamond and return its position among the neighbours
int Diamond::get_neighbour_index(Diamond* neighbour)
{
    for(int i=0;i<this->neighbours.size();i++)
    {
        if (this->neighbours[i]!=NULL)
        {
            if(this->neighbours[i]->get_id()==neighbour->get_id())
            {
                return i;
            }
        }
        
    }
    // both diamaonds are not adjacents
    assert(true==false);
    return -1;
}

void Diamond::set_central_edge(pair<int,int> edge)
{
    if (edge.first<edge.second)
    {
        this->central_edge=edge;
    }
    else
    {
        this->central_edge=pair<int,int>{edge.second,edge.first};
    }    
}

void Diamond::set_anchor_vertex(Vertex* anchor)
{
    if (this->has_anchor)
    {
        cout<<"already has an anchor"<<endl;
        assert(true==false);
    }
    this->anchor_vertex=anchor;
    this->vertex_order.clear();
    if (this->tetra_list.size()==1)
    {
        tuple<int,int,int> opposite_anchor_face=this->tetra_list[0]->get_opposite_face(anchor_vertex);
        this->neighbours_faces[0]=opposite_anchor_face;
        this->vertex_order.push_back(anchor_vertex->get_id());
        int x=1;
        for(int i=0;i<4;i++)
        {
            if (this->tetra_list[0]->get_vertices()[i]->get_id()!=anchor_vertex->get_id())
            {
                this->neighbours_faces[x]=this->tetra_list[0]->get_opposite_face(this->tetra_list[0]->get_vertices()[i]);
                this->vertex_order.push_back(this->tetra_list[0]->get_vertices()[i]->get_id());
                x++;
            }
        }
    }
    
}

void Diamond::display_vertices_id()
{
    for(int i : this->get_vertex_order())
    {
        cout<<i<<" ";
    }
    cout<<endl;
}


// return the order of the vertices id of a Diamond
// the n-2 first id are on the equator of the diamond
// then then last 2 are the anchor and its opposite vertex
vector<int> Diamond::get_vertex_order()
{
    vector<int> order;
    int south=-1;
    int north=-1;
    if (this->get_tetra_list().size()>1)
    {
        // we gather all vertices on the "equator" of the diamond (i.e are not on the extremities of the central edge)
        for (Tetrahedron* tetra : this->get_tetra_list())
        {
            if (tetra->get_vertices()[0]->get_id()!=this->get_central_edge().first && tetra->get_vertices()[0]->get_id()!=this->get_central_edge().second)
            {
                order.push_back(tetra->get_vertices()[0]->get_id());
            }
            if (tetra->get_vertices()[1]->get_id()!=this->get_central_edge().first && tetra->get_vertices()[1]->get_id()!=this->get_central_edge().second)
            {
                order.push_back(tetra->get_vertices()[1]->get_id());
            }
            if (tetra->get_vertices()[2]->get_id()!=this->get_central_edge().first && tetra->get_vertices()[2]->get_id()!=this->get_central_edge().second)
            {
                order.push_back(tetra->get_vertices()[2]->get_id());
            }
            if (tetra->get_vertices()[3]->get_id()!=this->get_central_edge().first && tetra->get_vertices()[3]->get_id()!=this->get_central_edge().second)
            {
                order.push_back(tetra->get_vertices()[3]->get_id());
            }
        }

        // we now have a list of vertices id on the equator
        // as we deal with a diamond, each vertex id should appear twice
        // we just have to make them appear in the good order and remove duplicate
        vector<int> final_order;
        for(int i=0;i<order.size()-2;i++)
        {
            if (order[i]==order[i+1] || order[i]==order[i+2])
            {
                final_order.push_back(order[i]);
            }
            if (i+3<order.size() && order[i]==order[i+3] && !(i==1 && order.size()==6))
            {
                final_order.push_back(order[i]);
            }
        }
        if (order[0]!=final_order[0])
        {
            final_order.insert(final_order.begin(),order[0]);
        }
        else
        {
            final_order.insert(final_order.begin(),order[1]);
        }
        
        if (this->anchor_vertex->get_id()==this->central_edge.first)
        {
            final_order.push_back(this->central_edge.first);
            final_order.push_back(this->central_edge.second);
        }
        else
        {
            final_order.push_back(this->central_edge.second);
            final_order.push_back(this->central_edge.first);
        }

        if (final_order.size()!=this->tetra_list.size()+2)
        {
            cout<<"Uncorrect number of vertices : "<<final_order.size()<<" instead of "<<this->tetra_list.size()+2<<endl;
            assert(true==false);
        }
        return final_order;
    }
    else
    {
        return this->vertex_order;
    }
        
}

