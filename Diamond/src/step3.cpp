#include "../include/step3.h"


void step_3_0_set_central_edge(vector<Diamond> &diamond_list,map<tuple<int,int>,vector<Tetrahedron*>> &edge_dict,
map<int,vector<Tetrahedron*>> &vertex_dict)
{
    map<int,int> vertex_taken;
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
            vertex_taken[central_vertices[0]]++;
            vertex_taken[central_vertices[1]]++;
        }       
    }

    // cout<<"vertex taken : "<<vertex_taken.size()<<endl;
    // unordered_set<int> xx;
    // int count_x=0;
    // for(pair<int,vector<Tetrahedron*>> vertex : vertex_dict)
    // {
    //     int count_isolated=0;
    //     if(vertex_taken.count(vertex.first)==0)
    //     {
    //         for(Tetrahedron* tetra : vertex.second)
    //         {
    //             if(tetra->get_diamond_ref()->get_tetra_list().size()==1)
    //             {
    //                 count_isolated++;
    //             }
    //         }
    //         if (count_isolated==0)
    //         {
    //             count_x++;
    //         }
    //     }
    // }
    // cout<<"count x : "<<count_x<<endl;


    // for(Diamond &diamond : diamond_list)
    // {
    //     if (diamond.get_tetra_list().size()==1)
    //     {
    //         int min_value=10000;
    //         tuple<int,int> min_edge;
    //         int min_size;
    //         for(tuple<int,int> edge : diamond.get_tetra_list()[0]->enumerate_edges())
    //         {
    //             int d=vertex_taken[get<0>(edge)]+vertex_taken[get<1>(edge)];
    //             if(d<min_value)
    //             {
    //                 min_edge=edge;
    //                 min_value=d;
    //                 min_size=count_if(vertex_dict[get<0>(edge)].begin(),vertex_dict[get<0>(edge)].end(),
    //                 [](Tetrahedron* i){return i->get_diamond_ref()->get_tetra_list().size()>1;});
    //                 min_size+=count_if(vertex_dict[get<1>(edge)].begin(),vertex_dict[get<1>(edge)].end(),
    //                 [](Tetrahedron* i){return i->get_diamond_ref()->get_tetra_list().size()>1;});
    //             }
    //             else if(d==min_value)
    //             {
    //                 int c = count_if(vertex_dict[get<0>(edge)].begin(),vertex_dict[get<0>(edge)].end(),
    //                     [](Tetrahedron* i){return i->get_diamond_ref()->get_tetra_list().size()>1;});
    //                     min_size+=count_if(vertex_dict[get<1>(edge)].begin(),vertex_dict[get<1>(edge)].end(),
    //                     [](Tetrahedron* i){return i->get_diamond_ref()->get_tetra_list().size()>1;});
    //                 if(c<min_size)
    //                 {
    //                     min_edge=edge;
    //                     min_size=c;
    //                 }
    //             }
    //         }
    //         diamond.set_central_edge(pair<int,int>{get<0>(min_edge),get<1>(min_edge)});
    //     }           
    // }
}


int minimum(map<int,vector<int>> &lala,vector<Diamond> &diamond_list)
{
    int min_value=1000;
    int min_key;
    for (pair<int,vector<int>> i : lala)
    {
        if (min_value>i.second.size())
        {
            min_key=i.first;
            min_value=i.second.size();
        }
        else if (min_value==i.second.size())
        {
            int a=0;
            int b=0;
            for (int j : i.second)
            {
                a+=2*diamond_list[j].get_tetra_list().size();
            }
            for (int j : lala[min_key])
            {
                b+=2*diamond_list[j].get_tetra_list().size();
            }
            if (a<b)
            {
                min_key=i.first;
                min_value=i.second.size();
            }
        }
    }
    return min_key;
}


int minimumm(vector<int> &vec,vector<Diamond> &diamond_list)
{
    int min_key;
    int min_value =0;
    for (int i : vec)
    {
        if (diamond_list[i].get_tetra_list().size()>min_value)
        {
            min_value=diamond_list[i].get_tetra_list().size();
            min_key=i;
        }
    }
    return min_key;
}


// this step aims at choosing an anchor vertex for each diamond
// such that any vertex is linked to only one diamond
void step_3_1_pair_vertices_as_anchor(vector<Diamond> &diamond_list,vector<Vertex> &vertex_list,
map<int,vector<Tetrahedron*>> &vertex_dict,map<tuple<int,int>,vector<Tetrahedron*>> &edge_dict)
{
    // auto cmp = [](pair<int,vector<int>> a, pair<int,vector<int>> b) { return a.second.size()<b.second.size(); };
    map<int,vector<int>> remaining_vertices;
    // set<pair<int,vector<int>>,decltype(cmp)> remaining_vertices(cmp);
    map<int,vector<int>> inverse;
    // vector<pair<int,vector<pair<int,int>>>> remaining_vertices;
    // auto cmp = [](pair<int,vector<pair<int,int>>> left, pair<int,vector<pair<int,int>>> right)
    //  { return left.second.size()<right.second.size();};
    // priority_queue<pair<int,vector<pair<int,int>>>,vector<pair<int,vector<pair<int,int>>>>,decltype(cmp)> queue(cmp);

    for (int i=0;i<diamond_list.size();i++)
    {
        if (diamond_list[i].get_tetra_list().size()>1)
        {
            remaining_vertices[diamond_list[i].get_central_edge().first].push_back(i);
            remaining_vertices[diamond_list[i].get_central_edge().second].push_back(i);
            inverse[i].push_back(diamond_list[i].get_central_edge().first);
            inverse[i].push_back(diamond_list[i].get_central_edge().second);
        }
        else
        {
            for (Vertex* vertex : diamond_list[i].get_tetra_list()[0]->get_vertices())
            {
                remaining_vertices[vertex->get_id()].push_back(i);
                inverse[i].push_back(vertex->get_id());
            }
        }
    }

    // for (pair<int,vector<int>> i : remaining_vertices2)
    // {
    //     remaining_vertices.insert(pair<int,vector<int>>{i.first,i.second});
    // }

    vector<pair<int,int>> app;

    // while there is a vertex not associated to an central edge and which is adjacent to a non paired central edge
    // cout<<"lets go"<<endl;

    vector<pair<int,vector<int>>> lala;

    for (pair<int,vector<int>> x : remaining_vertices)
    {
        lala.push_back({x.first,x.second});
    }

    std::sort(lala.begin(), lala.end(),[]( pair<int,vector<int>>& l, pair<int,vector<int>>& r) 
    {return l.second.size()<r.second.size();});
    
    // while(remaining_vertices.size()>0)  
    set<int> diamond_taken;  
    for (pair<int,vector<int>> w : lala)
    {
        // cout<<1<<endl;
        // auto it = min_element(remaining_vertices.begin(),remaining_vertices.end(),
        // [](pair<int,vector<int>> const i,pair<int,vector<int>> const j){return i.second.size()<j.second.size();});
        // cout<<2<<endl;
        // int v = minimum(remaining_vertices,diamond_list);
        int v = w.first;

        // int max_key;
        // int max_value =1000;
        // for (int i : remaining_vertices[v])
        // {
        //     if (diamond_list[i].get_tetra_list().size()>max_value)
        //     {
        //         max_value=diamond_list[i].get_tetra_list().size();
        //         max_key=i;
        //     }
        // }
        // int d =max_key;
        int d=-1;
        vector<int> tmp;
        for (int i: w.second)
        {
            if (diamond_taken.count(i)==0)
            {
                tmp.push_back(i);
                // d = i;
                // diamond_taken.insert(d);
                
                // break;
            }
        }
        if (tmp.size()>0)
        {
            d= minimumm(tmp,diamond_list);
            diamond_taken.insert(d);
            app.push_back({v,d});
        }
        // continue;

        // int v= it->first;

        // int d= it->second[0];
        // app.push_back(pair<int,int>{v,d});
        // // cout<<3<<endl;
        // vector<int> x;
        // for (int vertex : inverse[d])
        // {
        //     auto it = remaining_vertices.find({vertex,x});

        //     if (it!=remaining_vertices.end())
        //     {
        //         // remaining_vertices[vertex].erase(std::remove(remaining_vertices[vertex].begin(),
        //         // remaining_vertices[vertex].end(), d), remaining_vertices[vertex].end());
        //         // if (remaining_vertices[vertex].size()==0)
        //         // {
        //         //     remaining_vertices.erase(vertex);
        //         // }
        //         cout<<"ca va"<<endl;
        //     }
            

            
        // } 
        // remaining_vertices.erase({v,x});
        if (remaining_vertices.size()%1000==0)
        {
            cout<<remaining_vertices.size()/(double)vertex_list.size()<<endl;
        }
    }
    // key : id of vertex and value is the vector with the ids of the diamonds containing it
    // map<int,vector<int>> remaining_vertices;
    // map<int,vector<int>> inverse;
    // // vector<pair<int,vector<pair<int,int>>>> remaining_vertices;
    // // auto cmp = [](pair<int,vector<pair<int,int>>> left, pair<int,vector<pair<int,int>>> right)
    // //  { return left.second.size()<right.second.size();};
    // // priority_queue<pair<int,vector<pair<int,int>>>,vector<pair<int,vector<pair<int,int>>>>,decltype(cmp)> queue(cmp);

    // for (int i=0;i<diamond_list.size();i++)
    // {
    //     if (diamond_list[i].get_tetra_list().size()>1)
    //     {
    //         remaining_vertices[diamond_list[i].get_central_edge().first].push_back(i);
    //         remaining_vertices[diamond_list[i].get_central_edge().second].push_back(i);
    //         inverse[i].push_back(diamond_list[i].get_central_edge().first);
    //         inverse[i].push_back(diamond_list[i].get_central_edge().second);
    //     }
    //     else
    //     {
    //         for (Vertex* vertex : diamond_list[i].get_tetra_list()[0]->get_vertices())
    //         {
    //             remaining_vertices[vertex->get_id()].push_back(i);
    //             inverse[i].push_back(vertex->get_id());
    //         }
    //     }
    // }
    // vector<pair<int,int>> app;

    // while there is a vertex not associated to an central edge and which is adjacent to a non paired central edge
    // cout<<"lets go"<<endl;

    // while(remaining_vertices.size()>0)
    // {
    //     // cout<<1<<endl;
    //     // auto it = min_element(remaining_vertices.begin(),remaining_vertices.end(),
    //     // [](pair<int,vector<int>> const i,pair<int,vector<int>> const j){return i.second.size()<j.second.size();});
    //     // cout<<2<<endl;
    //     int v = minimum(remaining_vertices,diamond_list);

    //     // int max_key;
    //     // int max_value =1000;
    //     // for (int i : remaining_vertices[v])
    //     // {
    //     //     if (diamond_list[i].get_tetra_list().size()>max_value)
    //     //     {
    //     //         max_value=diamond_list[i].get_tetra_list().size();
    //     //         max_key=i;
    //     //     }
    //     // }
    //     // int d =max_key;
    //     int d =remaining_vertices[v][0];
    //     // int v= it->first;

    //     // int d= it->second[0];
    //     app.push_back(pair<int,int>{v,d});
    //     // cout<<3<<endl;
    //     for (int vertex : inverse[d])
    //     {
    //         remaining_vertices[vertex].erase(std::remove(remaining_vertices[vertex].begin(),
    //         remaining_vertices[vertex].end(), d), remaining_vertices[vertex].end());

    //         if (remaining_vertices[vertex].size()==0)
    //         {
    //             remaining_vertices.erase(vertex);
    //         }
    //     }
    //     remaining_vertices.erase(v);
    //     if (remaining_vertices.size()%1000==0)
    //     {
    //         cout<<remaining_vertices.size()/(double)vertex_list.size()<<endl;
    //     }
    // }

    set<int> a;
    set<int> b;

    for (pair<int,int> i : app)
    {
        a.insert(i.first);
        b.insert(i.second);
        diamond_list[i.second].set_anchor_vertex(&vertex_list[i.first]);
        diamond_list[i.second].has_anchor=true;
    }
    cout<<(double)a.size()/vertex_list.size()<<endl;
    cout<<(double)b.size()/vertex_list.size()<<endl;
    // assert(true==false);
}

// this function aims at associating all unassociated vertices of step_3 (around 0.1% of vertices)
// to do this, for each unpaired vertex, we break an adjacent diamond (containing at least 3 tetra)
// into several diamond of size 1 and put the vertex as the anchor of one of this diamond
void step_3_2_pair_unpaired_vertices(vector<Diamond> &diamond_list,vector<Vertex> &vertex_list,
map<int,vector<Tetrahedron*>> &vertex_dict)
{
    int w=0;
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
    // for (int i : unpaired_vertices)
    // {
    //     cout<<"unpaired id "<<i<<endl;
    // }
    cout<<"Share of vertices not associated to diamond or isolated tetra : "<<(double)unpaired_vertices.size()/vertex_list.size()<<endl;
    for(int vertex_id : unpaired_vertices)
    {
        bool paired=false;
        // Vertex vertex=vertex_list[vertex_id];
        // bool finished=false;
        // cout<<"unpaired vertex id : "<<vertex_id<<endl;
        for(Tetrahedron* tetra : vertex_dict[vertex_id])
        {
            // cout<<"size : "<<tetra->get_diamond_ref()->get_tetra_list().size()<<endl;
            if (tetra->get_diamond_ref()->get_tetra_list().size()>1)
            {
                // cout<<vertex_id<<endl;
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

                    // to match the unpaired vertice with one of the exploded tetra
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
                    // to match the old anchor vertex of the exploded diamond to an exploded tetra
                    // !a_taken is to not match the same tetra twice
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
                                ab=true;
                                break;
                            }
                        }
                    }   
                }
                if (a && b)
                {
                    diamond_list.insert( diamond_list.end(), c.begin(), c.end());
                    paired=true;
                    break;
                }
            }
        }
        if (!paired)
        {
            cout<<"unpaired :"<<vertex_id<<endl;
            for (Tetrahedron* tetra : vertex_dict[vertex_id])
            {
                if (!tetra->get_diamond_ref()->has_anchor)
                {
                    tetra->get_diamond_ref()->set_anchor_vertex(&vertex_list[vertex_id]);
                    tetra->get_diamond_ref()->has_anchor=true;
                    paired=true;
                    cout<<"paired"<<endl;
                }
            }
        }
        if (!paired)
        {
            w++;
        }
        // if (!paired)
        // {
        //     vector<Tetrahedron*> a;
        //     vector<Vertex*> b;

        //     for (Tetrahedron* tetra : vertex_dict[b.end()->get_id()])
        //     {
        //         if (tetra->get_diamond_ref()->get_tetra_list().size()==1)
        //         {
        //             a.push_back(tetra);
        //         }
        //     }


        //     for (Tetrahedron* tetra : vertex_dict[vertex_id])
        //     {
        //         if (tetra->get_diamond_ref()->get_tetra_list().size()==1 & tetra->get_diamond_ref()->has_anchor)
        //         {
        //             for (Tetrahedron* tetra2 : vertex_dict[tetra->get_diamond_ref()->get_anchor_vertex()->get_id()])
        //             {
        //                 if (tetra->get_diamond_ref()->get_tetra_list().size()==1 & !tetra->get_diamond_ref()->has_anchor)
        //                 {
        //                     tetra->get_diamond_ref()->set_anchor_vertex(&vertex_list[vertex_id]);
        //                     tetra2->get_diamond_ref()->set_anchor_vertex(tetra->get_diamond_ref()->get_anchor_vertex());
        //                     tetra2->get_diamond_ref()->has_anchor=true;
        //                     cout<<"Finally paired"<<endl;
        //                     break;
        //                 }
        //             }
        //         }
        //     }
        // }
    }
    cout<<"Nombre de conflits : "<<w<<endl;
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
            if (face==tuple<int,int,int>{0,0,1})
            {
                cout<<"problem "<<diamond.get_id()<<endl;
                assert(true==false);
            }
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
    // cout<<1<<endl;
    for (Diamond &diamond : diamond_list)
    {
        // cout<<2<<endl;
        if (diamond.has_anchor)
        {
            // // cout<<s2<<endl;
            anchor_dict[diamond.get_anchor_vertex()->get_id()]=&diamond;
            // cout<<3<<endls;
        }
    }
    cout<<"anchor dict done"<<endl;
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

    int fais_chier=-1;
    // because the last tetra has the vertice 0
    int size=focus.get_tetra_list().size();

    if (size==1)
    {
        if (index==0)
        {
            vertices={1,2,3};
        }
        if (index==1)
        {
            vertices={0,2,3};
        }
        if (index==2)
        {
            vertices={0,1,3};
        }
        if (index==3)
        {
            vertices={0,1,2};
        }
        
    }
    else
    {
        if (index%2==0)
        {
            if (index!=0 && (index/2+1)%size==0)
            {
                fais_chier=0;
                vertices={(index/2),0,size};
            }
            else
            {
                fais_chier=1;
                vertices={(index/2)%size,(index/2+1)%size,size};
            }
        }
        else
        {
            if (index-1!=0 && ((index-1)/2+1)%size==0)
            {
                fais_chier=2;
                vertices={((index-1)/2)%size,0,size+1};
            }
            else
            {
                fais_chier=3;
                vertices={((index-1)/2)%size,((index-1)/2+1)%size,size+1};
            }
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

    // if (focus.get_id()==6369 && neighbour->get_id()==476)
    // {
    //     for (int i : focus_order)
    //     {
    //         cout<<i<<" ";
    //     }
    //     cout<<endl;
    //     for (int i : neighbour_order)
    //     {
    //         cout<<i<<" ";
    //     }
    //     cout<<endl;
    //     cout<<permutation[0]<<" "<<permutation[1]<<" "<<permutation[2]<<" "<<neighbour_order.size()<<endl;
    //     cout<<vertices[0]<<" "<<vertices[1]<<" "<<vertices[2]<<endl;
    //     cout<<"fais_chier "<<fais_chier<<endl;
    //     cout<<"index "<<index<<endl;
    // }


    if (permutation.size()!=3)
    {
        cout<<"Permutation size : "<<permutation.size()<<endl;
        assert(true==false);
    }

    if (neighbour_order.size()!=4)
    {
        if (permutation[0]==(neighbour_order.size()-3))
        {
            if (permutation[1]==0)
            {
                return {0,1,2};
            }
            else if (permutation[2]==0)
            {
                return {0,2,1};
            }
        }
        if (permutation[1]==(neighbour_order.size()-3))
        {
            if (permutation[0]==0)
            {
                return {1,0,2};
            }
            else if (permutation[2]==0)
            {
                return {1,2,0};
            }
        }
        if (permutation[2]==(neighbour_order.size()-3))
        {
            if (permutation[0]==0)
            {
                return {2,0,1};
            }
            else if (permutation[1]==0)
            {
                return {2,1,0};
            }
        }
        if (permutation[0]==permutation[1]-1 && permutation[0]<neighbour_order.size()-3)
        {
            return {0,1,2};
        }
        if (permutation[0]==permutation[2]-1 && permutation[0]<neighbour_order.size()-3)
        {
            return {0,2,1};
        }     
        if (permutation[1]==permutation[0]-1 && permutation[1]<neighbour_order.size()-3)
        {
            return {1,0,2};
        }
        if (permutation[1]==permutation[2]-1 && permutation[1]<neighbour_order.size()-3)
        {
            return {1,2,0};
        }  
        if (permutation[2]==permutation[0]-1 && permutation[2]<neighbour_order.size()-3)
        {
            return {2,0,1};
        }  
        if (permutation[2]==permutation[1]-1 && permutation[2]<neighbour_order.size()-3)
        {
            return {2,1,0};
        }
    }
    else if (neighbour_order.size()==4)
    {
        if (permutation[0]<permutation[1] && permutation[1]<permutation[2])
        {
            return {0,1,2};
        }
        if (permutation[0]<permutation[2] && permutation[2]<permutation[1])
        {
            return {0,2,1};
        }
        if (permutation[1]<permutation[0] && permutation[0]<permutation[2])
        {
            return {1,0,2};
        }
        if (permutation[1]<permutation[2] && permutation[2]<permutation[0])
        {
            return {1,2,0};
        }
        if (permutation[2]<permutation[0] && permutation[0]<permutation[1])
        {
            return {2,0,1};
        }
        if (permutation[2]<permutation[1] && permutation[1]<permutation[0])
        {
            return {2,1,0};
        }
    }
    


    cout<<permutation[0]<<" "<<permutation[1]<<" "<<permutation[2]<<" "<<neighbour_order.size()<<endl;
    cout<<"fuck"<<endl;
    assert(true==false);   
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
                else if (diamond.get_tetra_list().size()==1 && diamond.get_neighbours()[i]->get_tetra_list().size()>1)
                {
                    vector<int> permutation = get_permutation(diamond,diamond.get_neighbours()[i],i);
                    diamond.set_permutation(permutation,i);
                }
            }
        }
    }
}