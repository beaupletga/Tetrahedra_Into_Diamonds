#include "../include/step3.h"


void step_3_0_set_central_edge(vector<Diamond> &diamond_list,map<tuple<int,int>,vector<Tetrahedron*>> &edge_dict,
map<int,vector<Tetrahedron*>> &vertex_dict)
{
    unordered_set<int> vertex_taken;
    for(Diamond &diamond : diamond_list)
    {
        if (diamond.get_tetra_list().size()>1)
        {
            unordered_map<int,int> vertex_frequency;
            for(Tetrahedron* tetra : diamond.get_tetra_list())
            {
                for(Vertex* vertex : tetra->get_vertices())
                {
                    vertex_frequency[vertex->get_id()]++;
                }
            }
            vector<int> central_vertices;
            for(pair<int,int> i : vertex_frequency)
            {
                if(i.second>2)
                {
                    central_vertices.push_back(i.first);
                }
            }
            // to check that the diamond is well formed (only 2 vertex appear more than twice)
            assert(central_vertices.size()==2);
            diamond.set_central_edge(pair<int,int>{central_vertices[0],central_vertices[1]});
            vertex_taken.insert(central_vertices[0]);
            vertex_taken.insert(central_vertices[1]);
        }       
    }

    // cout<<"vertex taken : "<<vertex_taken.size()<<endl;
    // unordered_set<int> xx;
    int count_x=0;
    for(pair<int,vector<Tetrahedron*>> vertex : vertex_dict)
    {
        int count_isolated=0;
        if(vertex_taken.count(vertex.first)==0)
        {
            for(Tetrahedron* tetra : vertex.second)
            {
                if(tetra->get_diamond_ref()->get_tetra_list().size()==1)
                {
                    count_isolated++;
                }
            }
            if (count_isolated==0)
            {
                count_x++;
            }
        }
    }
    cout<<"count x : "<<count_x<<endl;


    for(Diamond &diamond : diamond_list)
    {
        if (diamond.get_tetra_list().size()==1)
        {
            int min_value=10000;
            tuple<int,int> min_edge;
            int min_size;
            for(tuple<int,int> edge : diamond.get_tetra_list()[0]->enumerate_edges())
            {
                int d=vertex_taken.count(get<0>(edge))+vertex_taken.count(get<1>(edge));
                if(d<min_value)
                {
                    min_edge=edge;
                    min_value=d;
                    min_size=edge_dict[edge].size();
                }
                else if(d==min_value)
                {
                    if(edge_dict[edge].size()<min_size)
                    {
                        min_edge=edge;
                        min_size=edge_dict[edge].size();
                    }
                }
            }
            diamond.set_central_edge(pair<int,int>{get<0>(min_edge),get<1>(min_edge)});
        }           
    }
}


void cc(vector<Diamond> &diamond_list)
{
    int x=0;
    for(int i=0;i<diamond_list.size();i++)
    {
        if (diamond_list[i].has_anchor)
        {
           x++;
        }
    }
    cout<<"Nb Diamonds with anchor : "<<x<<endl;
}

// this step aims at choosing an anchor vertex for each diamond
// such that any vertex is linked to only one diamond
void step_3_1_pair_vertices_as_anchor(vector<Diamond> &diamond_list,vector<Vertex> &vertex_list,
map<int,vector<Tetrahedron*>> &vertex_dict,map<tuple<int,int>,vector<Tetrahedron*>> &edge_dict)
{
    // foreach vertex, we add to a list the central edges adjacent to it
    map<int,vector<pair<int,int>>> remaining_vertices;
    for(Diamond &diamond : diamond_list)
    {  
        int vertex1 =  diamond.get_central_edge().first;
        int vertex2 =  diamond.get_central_edge().second;
        remaining_vertices[vertex1].push_back(diamond.get_central_edge());
        remaining_vertices[vertex2].push_back(diamond.get_central_edge());
    }

    // while there is a vertex not associated to an central edge and which is adjacent to a non paired central edge
    while(remaining_vertices.size()>0)
    {
        // we choose the vertex with the smallest number of adjacent central edges
        pair<int,vector<pair<int,int>>> it = *min_element(remaining_vertices.begin(),remaining_vertices.end(),
        [](pair<int,vector<pair<int,int>>> i,pair<int,vector<pair<int,int>>> j){return i.second.size()<j.second.size();});
        // we pair this vertex to the first of its adjacent edges        
        pair<int,pair<int,int>> w = {it.first,{it.second[0]}};
        // we add this vertex as an anchor to the diamond of this central edge
        for(Diamond &diamond : diamond_list)
        {
            if(diamond.get_central_edge()==it.second[0])
            {
                diamond.set_anchor_vertex(&vertex_list[it.first]);
                diamond.has_anchor=true;
                break;
            }
        }
        remaining_vertices.erase(it.first);

        if (w.first==w.second.first && remaining_vertices.count(w.second.second)>0)
        {
            // deleting in map doesn't seem to work so I need to push back all elements except the one i want to delete
            vector<pair<int,int>> x;
            for(int k=0;k<remaining_vertices[w.second.second].size();k++)
            {
                if(remaining_vertices[w.second.second][k]!=w.second)
                {
                    x.push_back(remaining_vertices[w.second.second][k]);
                }
            }
            remaining_vertices[w.second.second]=x;

            if (remaining_vertices[w.second.second].size()==0)
                remaining_vertices.erase(w.second.second);
            
        }
        else if (w.first==w.second.second && remaining_vertices.count(w.second.first)>0)
        {
            vector<pair<int,int>> x;
            for(int k=0;k<remaining_vertices[w.second.first].size();k++)
            {
                if(remaining_vertices[w.second.first][k]!=w.second)
                {
                    x.push_back(remaining_vertices[w.second.first][k]);
                }
            }
            remaining_vertices[w.second.first]=x;

            if (remaining_vertices[w.second.first].size()==0)
                remaining_vertices.erase(w.second.first);
        }
    }
}

// this function aims at associating all unassociated vertices of step_3 (around 0.1% of vertices)
// to do this, for each unpaired vertex, we break an adjacent diamond (containing at least 3 tetra)
// into several diamond of size 1 and put the vertex as the anchor of one of this diamond
void step_3_2_pair_unpaired_vertices(vector<Diamond> &diamond_list,vector<Vertex> &vertex_list,
map<int,vector<Tetrahedron*>> &vertex_dict)
{
    int last_id= diamond_list.back().get_id()+1;
    unordered_set<int> unpaired_vertices;
    for(Vertex &vertex : vertex_list)
    {
        unpaired_vertices.insert(vertex.get_id());
    }
    for(Diamond &diamond : diamond_list)
    {
        if (diamond.has_anchor)
        {
            unpaired_vertices.erase(diamond.get_anchor_vertex()->get_id());
        }
    }
    cout<<"Number unpaired vertices : "<<unpaired_vertices.size()<<endl;
    for(int vertex_id : unpaired_vertices)
    {
        // Vertex vertex=vertex_list[vertex_id];
        // bool finished=false;
        // cout<<"vertex id : "<<vertex_id<<endl;
        for(Tetrahedron* tetra : vertex_dict[vertex_id])
        {
            // cout<<"size : "<<tetra->get_diamond_ref()->get_tetra_list().size()<<endl;
            if (tetra->get_diamond_ref()->get_tetra_list().size()>1)
            {
                int before= tetra->get_diamond_ref()->get_tetra_list().size();
                int ab=false;
                bool a=false;
                bool b=false;
                Diamond diamond1;
                Diamond diamond2;
                vector<Diamond> c;

                for(Tetrahedron* tetra2 : tetra->get_diamond_ref()->get_tetra_list())
                {
                    bool a_taken=false;
                    bool b_taken=false;
                    int v0,v1,v2,v3;
                    v0=tetra2->get_vertices()[0]->get_id();
                    v1=tetra2->get_vertices()[1]->get_id();
                    v2=tetra2->get_vertices()[2]->get_id();
                    v3=tetra2->get_vertices()[3]->get_id();
                    vector<int> v_list={v0,v1,v2,v3};
                    vector<Tetrahedron*> f = {tetra2};                       

                    if (!a)
                    {
                        for (int i=0;i<v_list.size();i++)
                        {
                            if (vertex_id==v_list[i])
                            {
                                a_taken=true;
                                diamond1 = Diamond(last_id,f,tetra2->get_vertices()[i],true);
                                last_id++;
                                a=true;
                                break;
                            }
                        }
                    }
                    if (!a_taken && !b)
                    {   
                        int anchor_id=tetra->get_diamond_ref()->get_anchor_vertex()->get_id();
                        for (int i=0;i<v_list.size();i++)
                        {
                            if (anchor_id==v_list[i])
                            {
                                diamond2 = Diamond(last_id,f,tetra->get_diamond_ref()->get_anchor_vertex(),true);
                                last_id++;
                                b=true;
                                b_taken=true;
                                break;
                            }
                        }
                    }
                    else if (!a_taken && !b_taken)
                    {
                        Diamond diamond3 = Diamond(last_id,f,NULL);
                        last_id++;
                        c.push_back(diamond3);
                    }


                    if (a && b && !ab)
                    {
                        for (int i=0;i<diamond_list.size();i++)
                        {
                            if (&diamond_list[i]==tetra->get_diamond_ref())
                            {
                                if (!diamond_list[i].has_anchor)
                                {
                                    diamond2.has_anchor=false;
                                }
                                c.push_back(diamond2);
                                diamond_list[i]=diamond1;
                                // v
                                ab=true;
                                break;
                            }
                        }
                        // break;
                    }   
                }
                if (a && b)
                {
                    diamond_list.insert( diamond_list.end(), c.begin(), c.end());
                    // cout<<"before : "<<before*2<<endl;
                    // cout<<"after : "<<4+c.size()*4<<endl;
                    // // cout<<ab<<endl;
                    // cout<<endl;

                    break;
                }
            }
        }
    }
}



void step_3_3_connectivity(vector<Diamond> &diamond_list)
{
    map<tuple<int,int,int>,vector<Diamond*>> external_faces_dict;
    // we add the external faces of each diamond to the dict
    // as soon as a face is shared by 2 tetra, we link the 2 diamonds
    for(Diamond &diamond : diamond_list)
    {
        for (tuple<int,int,int> face : diamond.get_external_faces())
        {
            if (external_faces_dict.count(face)==0)
            {
                external_faces_dict[face]={&diamond};
            }
            else
            {
                external_faces_dict[face].push_back(&diamond);
                external_faces_dict[face][0]->add_neighbour(face,external_faces_dict[face][1]);
                external_faces_dict[face][1]->add_neighbour(face,external_faces_dict[face][0]);
            }
        }
    }
}


map<int,Diamond*> step_3_4_anchor_dict(vector<Diamond> &diamond_list)
{
    map<int,Diamond*> anchor_dict;
    for (Diamond &diamond : diamond_list)
    {
        if (diamond.has_anchor)
        {
            anchor_dict[diamond.get_anchor_vertex()->get_id()]=&diamond;
        }
    }
    return anchor_dict;
}

// at the ith face, if i%2=0 => there are the vertices i/2 et i/2 +1
// at the ith face, if i%2=1 => there are the vertices i-1/2 et i-1/2 +1
vector<int> get_permutation(Diamond focus, Diamond* neighbour,int index)
{
    vector<int> focus_order = focus.get_vertex_order();
    vector<int> neighbour_order = neighbour->get_vertex_order();

    vector<int> vertices;
    vector<int> permutation;

    // because the last tetra has the vertice 0
    int size=focus.get_tetra_list().size();

    if (focus.get_tetra_list().size()==1)
    {
        vertices={0,1,2,3};
    }
    else
    {
        if (index%2==0)
        {
            vertices={(index/2)%size,(index/2+1)%size ,(focus_order.size()-2)};
        }
        else
        {
            vertices={((index-1)/2)%size,((index-1)/2+1)%size,(focus_order.size()-1)};
        }
    }
        
    for(int i : vertices)
    {
        for (int j=0;j<neighbour_order.size();j++)
        {
            if (focus_order[i]==neighbour_order[j])
            {
                permutation.push_back(j);
            }
        }
    }

    // cout<< focus_order.size()<<" "<<neighbour_order.size()<<" "<<index<<endl;
    if (permutation.size()==3)
    {
        if (permutation[0]==neighbour_order.size()-2 || permutation[0]==neighbour_order.size()-1)
        {
            if (permutation[1]==permutation[2]-1)
            {
                return {2,0,1};
            }
            else if (permutation[1]==neighbour_order.size()-3 && permutation[2]==0)
            {
                return {2,0,1};
            }
            else
            {
                return {2,1,0};
            }
        }
        else if (permutation[1]==neighbour_order.size()-2 || permutation[1]==neighbour_order.size()-1)
        {
            if (permutation[0]==permutation[2]-1)
            {
                return {0,2,1};
            }
            else if (permutation[0]==neighbour_order.size()-3 && permutation[2]==0)
            {
                return {0,2,1};
            }
            else
            {
                return {1,2,0};
            }
        }
        else if (permutation[2]==neighbour_order.size()-2 || permutation[2]==neighbour_order.size()-1)
        {
            if (permutation[0]==permutation[1]-1 && permutation[1]<permutation[2])
            {
                return {0,1,2};
            }
            else if (permutation[0]==neighbour_order.size()-3 && permutation[1]==0)
            {
                return {0,1,2};
            }
            else
            {
                return {1,0,2};
            }
        }
    }
    else
    {
        cout<<"Permutation size : "<<permutation.size()<<endl;
        assert(true==false);
    }
    return permutation;
}

void step_3_5_set_neighbour_permutation(vector<Diamond> &diamond_list)
{
    for(Diamond &diamond : diamond_list)
    {
        for(int i=0;i<diamond.get_neighbours().size();i++)
        {
            if (diamond.get_neighbours()[i]!=NULL)
            {
                if(diamond.get_tetra_list().size()>1 && diamond.get_neighbours()[i]->get_tetra_list().size()>1)
                {
                    vector<int> permutation = get_permutation(diamond,diamond.get_neighbours()[i],i);
                    diamond.set_permutation(permutation,i);
                }
                else if (diamond.get_tetra_list().size()>1 && diamond.get_neighbours()[i]->get_tetra_list().size()==1)
                {
                    vector<int> permutation = get_permutation(diamond,diamond.get_neighbours()[i],i);
                    diamond.set_permutation(permutation,i);
                }
                else if (diamond.get_tetra_list().size()==1 && diamond.get_neighbours()[i]->get_tetra_list().size()==1)
                {
                    vector<int> permutation = get_permutation(diamond,diamond.get_neighbours()[i],i);
                    diamond.set_permutation(permutation,i);
                }
            }
        }
    }
    for(Diamond &diamond : diamond_list)
    {
        for(int i=0;i<diamond.get_neighbours().size();i++)
        {
            if (diamond.get_neighbours()[i]!=NULL)
            {
                if (diamond.get_tetra_list().size()==1 && diamond.get_neighbours()[i]->get_tetra_list().size()>1)
                {
                    for(int j=0;j<4;j++)
                    {
                        for (int k=0;k<diamond.get_neighbours()[i]->neighbours_faces.size();k++)
                        {
                            if (diamond.neighbours_faces[j]==diamond.get_neighbours()[i]->neighbours_faces[k])
                            {
                                vector<int> permutation = diamond.get_neighbours()[i]->get_permutation(k);
                                diamond.set_permutation(permutation,j);
                            }
                        }
                    }
                }
            }
        }
    }
}