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


int minimum(map<int,vector<Diamond*>> &lala)
{
    int min_value=100;
    int min_key;
    for (pair<int,vector<Diamond*>> i : lala)
    {
        if (min_value>i.second.size())
        {
            min_key=i.first;
            min_value=i.second.size();
        }
    }
    return min_key;
}

// this step aims at choosing an anchor vertex for each diamond
// such that any vertex is linked to only one diamond
void step_3_1_pair_vertices_as_anchor(vector<Diamond> &diamond_list,vector<Vertex> &vertex_list,
map<int,vector<Tetrahedron*>> &vertex_dict,map<tuple<int,int>,vector<Tetrahedron*>> &edge_dict)
{

    map<int,vector<int>> remaining_vertices;
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
    vector<pair<int,int>> app;

    // while there is a vertex not associated to an central edge and which is adjacent to a non paired central edge
    while(remaining_vertices.size()>0)
    {
        // cout<<1<<endl;
        auto it = min_element(remaining_vertices.begin(),remaining_vertices.end(),
        [](pair<int,vector<int>> const i,pair<int,vector<int>> const j){return i.second.size()<j.second.size();});
        // cout<<2<<endl;
        int v= it->first;

        int min_value=1000;
        int min_key;
        for (int i : remaining_vertices[v])
        {
            if (inverse[i].size()<min_value)
            {
                min_value=inverse[i].size();
                min_key=i;
            }
        }
        int d = min_key;
        // int d= it->second[0];
        app.push_back(pair<int,int>{v,d});
        // cout<<3<<endl;
        for (int vertex : inverse[d])
        {
            remaining_vertices[vertex].erase(std::remove(remaining_vertices[vertex].begin(),
            remaining_vertices[vertex].end(), d), remaining_vertices[vertex].end());

            if (remaining_vertices[vertex].size()==0)
            {
                remaining_vertices.erase(vertex);
            }
        }
        remaining_vertices.erase(v);
        if (remaining_vertices.size()%1000==0)
        {
            cout<<remaining_vertices.size()/(double)vertex_list.size()<<endl;
        }

        // cout<<1<<endl;
        // // we choose the vertex with the smallest number of adjacent central edges
        // cout<<"taille1 "<<remaining_vertices.size()<<endl;
        // // auto it = min_element(remaining_vertices.begin(),remaining_vertices.end(),
        // // [](pair<int,vector<Diamond*>> const i,pair<int,vector<Diamond*>> const j){return i.second.size()<j.second.size();});
        
        // int h = minimum(remaining_vertices);
        // // if (it.second.size()==0)
        // // {
        // //     remaining_vertices.erase(it.first);
        // //     continue;
        // // }

        // cout<<1.5<<" "<<h<<" "<<remaining_vertices.count(h)<<endl;
        // // // we pair this vertex to the first of its adjacent edges        
        // int selected_id  = remaining_vertices[h][0]->get_id();
        // // we add this vertex as an anchor to the diamond of this central edge

        // // int min_value=1000;
        // // for (pair<int,int> i : it.second)
        // // {
        // //     if (edge_dict[i].size()<min_value)
        // //     {
        // //         min_pair=i;
        // //         min_value=edge_dict[i].size();
        // //     }
        // // }
        // cout<<2<<" "<<remaining_vertices[h].size()<<endl;
        // diamond_list[selected_id].set_anchor_vertex(&vertex_list[h]);
        // diamond_list[selected_id].has_anchor=true;
        // if (diamond_list[selected_id].get_tetra_list().size()==1)
        // {
        //     cout<<3<<endl;
        //     cout<<"it "<<h<<" "<<remaining_vertices[h].size()<<endl;
        //     cout<<3.1<<endl;
        //     for (int vertex : diamond_list[selected_id].get_vertices_id())
        //     {
        //         cout<<vertex<<" "<<3.2<<endl;
        //         for (int i=0;i<remaining_vertices[vertex].size();i++)
        //         {
        //             cout<<3.21<<endl;
        //             if (remaining_vertices[vertex][i]->get_id()==selected_id)
        //             {
        //                 cout<<3.25<<endl;
        //                 remaining_vertices[vertex].erase(remaining_vertices[vertex].begin()+i);
        //                 cout<<3.45<<" "<<remaining_vertices[vertex].size()<<endl;
        //                 if (remaining_vertices[vertex].size()==0)
        //                 {
        //                     auto it=remaining_vertices.find(vertex);
        //                     remaining_vertices.erase (it);      
        //                     // remaining_vertices.erase(vertex);
        //                     cout<<"size "<<remaining_vertices.count(vertex)<<endl;
        //                     if (remaining_vertices.count(vertex)==0)
        //                     {
        //                         cout<<vertex<<" is deleted"<<endl;
        //                     }
        //                     // break;
        //                 }
        //             }
        //         }
        //     }
        //     cout<<3.5<<endl;
        // }
        // cout<<"taille2 "<<remaining_vertices.size()<<endl;
        // // else
        // // {
        // //     cout<<4<<endl;           

        // //     int id_to_clean;
        // //     cout<<"central edge "<<diamond_list[selected_id].get_central_edge().first<<" "<<diamond_list[selected_id].get_central_edge().second<<endl;
        // //     if (it->first==diamond_list[selected_id].get_central_edge().first)
        // //     {
        // //         id_to_clean=diamond_list[selected_id].get_central_edge().second;
        // //     }
        // //     else
        // //     {
        // //         id_to_clean=diamond_list[selected_id].get_central_edge().first;
        // //     }

        // //     for (int i=0;i<remaining_vertices[id_to_clean].size();i++)
        // //     {
        // //         if (remaining_vertices[id_to_clean][i]->get_id()==selected_id)
        // //         {
        // //             remaining_vertices[id_to_clean].erase(remaining_vertices[id_to_clean].begin()+i);
        // //             cout<<"size0 "<<remaining_vertices[id_to_clean].size()<<endl;
        // //             if (remaining_vertices[id_to_clean].size()==0)
        // //             {
        // //                 remaining_vertices.erase(id_to_clean);
        // //                 cout<<"size "<<remaining_vertices.count(id_to_clean)<<endl;
        // //             }
        // //         }
        // //     }
        // // }
        // remaining_vertices.erase(h);
        // cout<<"taille2 "<<remaining_vertices.size()<<endl;
        // if (remaining_vertices.size()%1000==0)
        // {
        //     cout<<remaining_vertices.size()/(double)vertex_list.size()<<endl;
        // }
    }

    for (pair<int,int> i : app)
    {
        diamond_list[i.second].set_anchor_vertex(&vertex_list[i.first]);
        diamond_list[i.second].has_anchor=true;
    }

    cout<<"over"<<endl;
    // foreach vertex, we add to a list the central edges adjacent to it
    // map<int,vector<pair<int,int>>> remaining_vertices;
    // // vector<pair<int,vector<pair<int,int>>>> remaining_vertices;
    // // auto cmp = [](pair<int,vector<pair<int,int>>> left, pair<int,vector<pair<int,int>>> right)
    // //  { return left.second.size()<right.second.size();};
    // // priority_queue<pair<int,vector<pair<int,int>>>,vector<pair<int,vector<pair<int,int>>>>,decltype(cmp)> queue(cmp);


    // for(Diamond &diamond : diamond_list)
    // {  
    //     if (diamond.get_tetra_list().size()>1)
    //     {
    //         int vertex1 =  diamond.get_central_edge().first;
    //         int vertex2 =  diamond.get_central_edge().second;
    //         remaining_vertices[vertex1].push_back(diamond.get_central_edge());
    //         remaining_vertices[vertex2].push_back(diamond.get_central_edge());
    //     }
    //     else
    //     {
    //         for (tuple<int,int> edge : diamond.get_tetra_list()[0]->enumerate_edges())
    //         {
    //             remaining_vertices[get<0>(edge)].push_back(pair<int,int>{get<0>(edge),get<1>(edge)});
    //             remaining_vertices[get<1>(edge)].push_back(pair<int,int>{get<0>(edge),get<1>(edge)});
    //         }
    //     }
    // }

    // // we check that every vertex is adjacent to at least one central edge
    // // otherwise we won't be able to pair it with a diamond
    // int count=0;
    // for (int i=0;i<vertex_list.size();i++)
    // {
    //     if (remaining_vertices.count(vertex_list[i].get_id())==0)
    //     {
    //         count++;
    //     }
    // }
    // cout<<count<< " vertices are not adjacent to any central edge"<<endl;

    // // while there is a vertex not associated to an central edge and which is adjacent to a non paired central edge
    // while(remaining_vertices.size()>0)
    // {
    //     cout<<1<<endl;
    //     // we choose the vertex with the smallest number of adjacent central edges
    //     pair<int,vector<pair<int,int>>> it = *min_element(remaining_vertices.begin(),remaining_vertices.end(),
    //     [](pair<int,vector<pair<int,int>>> i,pair<int,vector<pair<int,int>>> j){return i.second.size()<j.second.size();});
        
    //     // // we pair this vertex to the first of its adjacent edges        
    //     // pair<int,pair<int,int>> w = {it.first,{it.second[0]}};
    //     // we add this vertex as an anchor to the diamond of this central edge

    //     cout<<it.first<<" "<<it.second.size()<<" "<< 2<<endl;
    //     pair<int,int> min_pair = it.second[0];
    //     // int min_value=1000;
    //     // for (pair<int,int> i : it.second)
    //     // {
    //     //     if (edge_dict[i].size()<min_value)
    //     //     {
    //     //         min_pair=i;
    //     //         min_value=edge_dict[i].size();
    //     //     }
    //     // }

    //     cout<<3<<endl;
    //     pair<int,pair<int,int>> w = {it.first,{min_pair}};  

    //     for (Tetrahedron* tetra : edge_dict[min_pair])
    //     {
    //         if (tetra->get_diamond_ref()->get_central_edge()==min_pair)
    //         {
    //             tetra->get_diamond_ref()->set_anchor_vertex(&vertex_list[it.first]);
    //             tetra->get_diamond_ref()->has_anchor=true;
    //             break;
    //         }
    //     }
    //     cout<<4<<endl;
    //     int vertex_to_check;
    //     if (w.first==w.second.first)
    //     {
    //         vertex_to_check=w.second.second;
    //     }
    //     else
    //     {
    //         vertex_to_check=w.second.first;
    //     }
       
    //     cout<<5<<endl;
    //     for (int i=0;i<remaining_vertices[vertex_to_check].size();i++)
    //     {
    //         if (remaining_vertices[vertex_to_check][i]==w.second)
    //         {
    //             remaining_vertices[vertex_to_check].erase(remaining_vertices[vertex_to_check].begin() + i);
    //             if (remaining_vertices[vertex_to_check].size()==0)
    //             {
    //                 remaining_vertices.erase(vertex_to_check);
    //                 cout<<"after "<<remaining_vertices.count(vertex_to_check)<<endl;
    //             }
    //             break;
    //         }
    //     }
    //     cout<<6<<endl;
    //     remaining_vertices.erase(w.first);
    //     cout<<7<<endl;
    // }

        // remaining_vertices[w.second.first].
        // remaining_vertices[w.second.second].erase(it.second);

    // while(remaining_vertices.size()>0)
    // {
    //     pair<int,vector<pair<int,int>>> it = *min_element(remaining_vertices.begin(),remaining_vertices.end(),
    //     [](pair<int,vector<pair<int,int>>> i,pair<int,vector<pair<int,int>>> j){return i.second.size()<j.second.size();});
    //     // we pair this vertex to the first of its adjacent edges        
    //     pair<int,pair<int,int>> w = {it.first,{it.second[0]}};
    //     // we add this vertex as an anchor to the diamond of this central edge
    //     for(Diamond &diamond : diamond_list)
    //     {
    //         if(diamond.get_central_edge()==it.second[0])
    //         {
    //             diamond.set_anchor_vertex(&vertex_list[it.first]);
    //             diamond.has_anchor=true;
    //             break;
    //         }
    //     }
    //     remaining_vertices.erase(it.first);

    //     if (w.first==w.second.first && remaining_vertices.count(w.second.second)>0)
    //     {
    //         // deleting in map doesn't seem to work so I need to push back all elements except the one i want to delete
    //         vector<pair<int,int>> x;
    //         for(int k=0;k<remaining_vertices[w.second.second].size();k++)
    //         {
    //             if(remaining_vertices[w.second.second][k]!=w.second)
    //             {
    //                 x.push_back(remaining_vertices[w.second.second][k]);
    //             }
    //         }
    //         remaining_vertices[w.second.second]=x;

    //         if (remaining_vertices[w.second.second].size()==0)
    //             remaining_vertices.erase(w.second.second);
            
    //     }
    //     else if (w.first==w.second.second && remaining_vertices.count(w.second.first)>0)
    //     {
    //         vector<pair<int,int>> x;
    //         for(int k=0;k<remaining_vertices[w.second.first].size();k++)
    //         {
    //             if(remaining_vertices[w.second.first][k]!=w.second)
    //             {
    //                 x.push_back(remaining_vertices[w.second.first][k]);
    //             }
    //         }
    //         remaining_vertices[w.second.first]=x;

    //         if (remaining_vertices[w.second.first].size()==0)
    //             remaining_vertices.erase(w.second.first);
    //     }
    //     if (remaining_vertices.size()%1000==0)
    //     {
    //         cout<<remaining_vertices.size()/(double)vertex_list.size()<<endl;
    //     }
    // }

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