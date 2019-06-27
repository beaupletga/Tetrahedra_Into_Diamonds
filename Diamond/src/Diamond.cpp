#include "../include/Diamond.h"


Diamond::Diamond()
{
    
}


// constructor for each diamond
// we know that the set of tetra shape as a cycle
Diamond::Diamond(int id,vector<Tetrahedron*>& elements,Vertex* anchor_vertex)
{
    this->id=id;
    this->has_anchor=false;
    bool already_in=false;
    this->tetra_list.push_back(elements[0]);
    this->anchor_vertex=anchor_vertex;
    if (elements.size()==1)
    {
        this->neighbours={NULL,NULL,NULL,NULL};
        this->neighbours_faces={{0,0,0},{0,0,0},{0,0,0},{0,0,0}};
    }
    else
    {
        for(int i=0;i<elements.size()*2;i++)
        {
            this->neighbours.push_back(NULL);
            this->neighbours_faces.push_back({0,0,0});
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


vector<tuple<int,int,int>> Diamond::get_external_faces()
{
    map<tuple<int,int,int>,int> faces;
    vector<tuple<int,int,int>> external_faces;
    // put faces in dictionary
    for (Tetrahedron* tetra : this->tetra_list)
    {
        for (tuple<int,int,int> face : tetra->enumerate_faces())
        {
            if (faces.count(face)==0)
            {
                faces[face]=1;
            }
            else
            {
                faces[face]+=1;
            }
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


void Diamond::add_neighbour(tuple<int,int,int> &face,Diamond* neighbour)
{
    // cout<<this->tetra_list.size()<<endl;
    // if the diamond has n tetra => 2*n external faces
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
            }
        }
    }
    
    else
    {
        if (this->has_anchor)
        {
            int anchor_id = this->anchor_vertex->get_id();
            if (anchor_id!=get<0>(face) && anchor_id!=get<1>(face) && anchor_id!=get<2>(face))
            {
                this->neighbours[3]=neighbour;
                this->neighbours_faces[3]=face;
            }
            else
            {
                int x=0;
                for (int i=0;i<4;i++)
                {
                    int id =this->tetra_list[0]->get_vertices()[i]->get_id();
                    if (id!=anchor_id)
                    {
                        if (id!=get<0>(face) && id!=get<1>(face) && id!=get<2>(face))
                        {
                            this->neighbours[x]=neighbour;
                            // this->neighbours_faces[x]=face;
                        }
                        x++;
                    }
                }
            }
        }
        else
        {
            // if the diamond has only one tetra => 4 external faces
            // we order the face by the vertice not belonging to the face
            // example : tetra (1,2,3,4)
            // the order of the faces is : 234 134 124 123
            for (int i=0;i<4;i++)
            {
                int id =this->tetra_list[0]->get_vertices()[i]->get_id();
                if (id!=get<0>(face) && id!=get<1>(face) && id!=get<2>(face))
                {
                    this->neighbours[i]=neighbour;
                    this->neighbours_faces[i]=face;
                    break;
                }
            }
        }        
    }
}


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
    // warning !!
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
    this->anchor_vertex=anchor;
}

void Diamond::display_vertices_id()
{
    unordered_set<int> tmp;
    for(Tetrahedron* tetra : this->tetra_list)
    {
        for(Vertex* vertex : tetra->get_vertices())
        {
            tmp.insert(vertex->get_id());
        }
    }
    for(int i : tmp)
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
    if (this->get_tetra_list().size()>1)
    {
        we use a step of 2 because face 0 and 1 share the same 2 vertices (2 and 3, 4 and 5 ...)
        for(int i=0;i<this->neighbours_faces.size();i+=2)
        {
            tuple<int,int,int> x;
            // this face is on the boundary
            if (neighbours_faces[i]==tuple<int,int,int>{0,0,0})
            {
                x=neighbours_faces[i+1];
            }
            else
            {
                x = neighbours_faces[i];
            }
            // we only use the edge on the equator for determining the order
            // we add the north and south at the end
            if(get<0>(x)==this->get_central_edge().first || get<0>(x)==this->get_central_edge().second)
            {
                order.push_back(get<1>(x));order.push_back(get<2>(x));
            }
            else if (get<1>(x)==this->get_central_edge().first || get<1>(x)==this->get_central_edge().second)
            {
                order.push_back(get<0>(x));order.push_back(get<2>(x));
            }
            else if (get<2>(x)==this->get_central_edge().first || get<2>(x)==this->get_central_edge().second)
            {
                order.push_back(get<0>(x));order.push_back(get<1>(x));
            }
            else
            {
                // a face doesn't contain any vertex from the central edge
                // or 2 faces of the same tetra are on the boundary
                assert(true==false);
            }            
        }
        
        // for(int x: order)
        // {
        //     cout<<x<<" ";
        // }
        // cout<<endl;
        // we now have a list of vertices id on the equator
        // as we deal with a diamond, each vertex id should appear twice

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

        // for(int x: final_order)
        // {
        //     cout<<x<<" ";
        // }
        // cout<<endl;
        // cout<<endl;
        // cout<<"Number of vertices : "<<final_order.size()<<" instead of "<<this->tetra_list.size()+2<<endl;
        if (final_order.size()!=this->tetra_list.size()+2)
        {
            cout<<"Uncorrect number of vertices : "<<final_order.size()<<" instead of "<<this->tetra_list.size()+2<<endl;
            assert(true==false);
        }
        // for(int x: final_order)
        // {
        //     cout<<x<<" ";
        // }
        return final_order;
    }
}

