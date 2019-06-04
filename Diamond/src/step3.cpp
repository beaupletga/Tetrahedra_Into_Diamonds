#include "../include/step3.h"


void set_central_edge(vector<Diamond> &diamond_list,map<tuple<int,int>,vector<Tetrahedron*>> &edge_dict,
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
void step_3(vector<Diamond> &diamond_list,vector<Vertex> &vertex_list,map<int,vector<Tetrahedron*>> &vertex_dict)
{
    map<int,vector<pair<int,int>>> tmp;
    for(Diamond diamond : diamond_list)
    {  
        int vertex1 =  diamond.get_central_edge().first;
        int vertex2 =  diamond.get_central_edge().second;
        tmp[vertex1].push_back(diamond.get_central_edge());
        tmp[vertex2].push_back(diamond.get_central_edge());
    }
    map<pair<int,int>,int> lalaa;
    while(tmp.size()>0)
    {
        pair<int,vector<pair<int,int>>> it = *min_element(tmp.begin(),tmp.end(),[](pair<int,vector<pair<int,int>>> i,pair<int,vector<pair<int,int>>> j){return i.second.size()<j.second.size();});
        // cout<<it.first<<it.second.size()<<endl;
        pair<int,pair<int,int>> w = {it.first,{it.second[0]}};
        for(Diamond &diamond : diamond_list)
        {
            if(diamond.get_central_edge()==it.second[0])
            {
                diamond.set_anchor_vertex(&vertex_list[it.first]);
                diamond.has_anchor=true;
                break;
            }
        }
        if (lalaa.count(it.second[0])>0)
        {
            assert(true==false);
        }
        else
        {
            lalaa[it.second[0]]=it.first;
        }

        tmp.erase(it.first);
        for(pair<int,vector<pair<int,int>>> j : tmp)
        {
            for(int k=0;k<j.second.size();k++)
            {
                if(j.second[k]==w.second)
                {
                    vector<pair<int,int>> w;
                    for(pair<int,int> c  : j.second)
                    {
                        if(c!=j.second[k])
                        {
                            w.push_back(c);
                        }
                    }
                    tmp[j.first]=w;
                    break;
                }
            }
            if(tmp[j.first].size()==0)
            {
                tmp.erase(j.first);
            }
        }
    }
    cc(diamond_list);

    cout<<endl;
    int x=0;

    for(Vertex vertex : vertex_list)
    {
        bool is_in=false;
        for(pair<pair<int,int>,int> i : lalaa)
        {
            if (i.second==vertex.get_id())
            {
                is_in=true;
                break;
            }
        }
        if(!is_in)
        {
            // x++;
            bool finished=false;
            
            for(Tetrahedron* tetra : vertex_dict[vertex.get_id()])
            {
                if (tetra->get_diamond_ref()->get_tetra_list().size()>1 && !finished)
                {
                    // cout<<"ID : "<<tetra->get_diamond_ref()->get_id()<<endl;
                    bool a=false;
                    bool b=false;
                    Diamond diamond1,diamond2;
                    // bool not_finish=true;
                    // cout<<tetra->get_diamond_ref()->get_anchor_vertex()->get_id()<<endl;
                    // cout<<endl;
                    // cout<<"Anchor Id : "<<tetra->get_diamond_ref()->get_anchor_vertex()->get_id()<<endl;
                    // cout<<"Vertex id : "<<vertex.get_id()<<endl;
                    vector<Diamond> c;
                    for(Tetrahedron* tetra2 : tetra->get_diamond_ref()->get_tetra_list())
                    {
                        int v0,v1,v2,v3;
                        v0=tetra2->get_vertices()[0]->get_id();
                        v1=tetra2->get_vertices()[1]->get_id();
                        v2=tetra2->get_vertices()[2]->get_id();
                        v3=tetra2->get_vertices()[3]->get_id();
                        vector<int> v_list={v0,v1,v2,v3};
                        vector<Tetrahedron*> f = {tetra2};
                        // cout<<v0<<" "<<v1<<" "<<v2<<" "<<v3<<endl;
                        // tetra2->display_vertices_id();
                        
                        bool a_taken=false;
                        bool b_taken=false;
                        
                        if (!a)
                        {
                            for (int i=0;i<v_list.size();i++)
                            {
                                if (vertex.get_id()==v_list[i])
                                {
                                    a_taken=true;
                                    // cout<<"SOLO VERTEX"<<endl;
                                    // cc(diamond_list);
                                    diamond1 = Diamond(diamond_list.back().get_id()+1,f,tetra2->get_vertices()[i]);
                                    diamond1.has_anchor=true;
                                    // lalaa.push_back(pair<int,pair<int,int>>{v0,{0,0}});
                                    // lalaa[{0,0}]=v0;
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
                                    // cout<<"ANCHOR"<<endl;
                                    
                                    diamond2 = Diamond(diamond_list.back().get_id()+1,f,tetra->get_diamond_ref()->get_anchor_vertex());
                                    diamond2.has_anchor=true;
                                    // lalaa.push_back(pair<int,pair<int,int>>{v0,{0,0}});
                                    b=true;
                                    b_taken=true;
                                    break;
                                }
                            }
                        }
                        else if (!a_taken && !b_taken)
                        {
                            Diamond diamond3 = Diamond(diamond_list.back().get_id()+1,f,tetra->get_diamond_ref()->get_anchor_vertex());
                            c.push_back(diamond3);
                        }


                        if (a && b && !finished)
                        {
                            // cout<<"oui"<<endl;
                            for (int i=0;i<diamond_list.size();i++)
                            {
                                if (&diamond_list[i]==tetra->get_diamond_ref())
                                {
                                    // cout<<x<<" "<<diamond_list[i].has_anchor<<" ";
                                    
                                    if (diamond_list[i].has_anchor)
                                    {
                                        // diamond_list[i]=diamond1;
                                        diamond_list.push_back(diamond2);
                                    }
                                    else
                                    {
                                        // diamond_list[i]=diamond1;
                                        c.push_back(diamond2);
                                    }
                                    diamond_list[i]=diamond1;
                                    // cout<<c.size()<<" ";
                                    // cout<<diamond_list.size()<<endl;
                                    // diamond_list.erase(diamond_list.begin()+i);
                                    // cout<<x<<endl;
                                    
                                    x++;
                                    // cc(diamond_list);
                                    // cout<<endl;
                                    finished=true;
                                    break;
                                }
                            }
                        }   
                    }
                    if (a && b)
                    {
                        diamond_list.insert( diamond_list.end(), c.begin(), c.end());
                    }
                }
            }
        }   
    }
    cout<<"x : "<<x<<endl;
}


void step_3_bis(vector<Diamond> &diamond_list,vector<Vertex> &vertex_list,map<int,vector<Tetrahedron*>> &vertex_dict)
{

}
