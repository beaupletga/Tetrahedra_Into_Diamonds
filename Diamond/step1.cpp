#include "step1.h"

bool is_cycle(vector<Tetrahedron*>& tetra_list)
{
    map<int,int> count_vertex;
    for (int i=0;i<tetra_list.size();i++)
    {
        for (Vertex* j : tetra_list[i]->get_vertices())
        {
            if (count_vertex.count(j->get_id())==0)
            {
                count_vertex.insert({j->get_id(),1});
            }
            else
            {
                count_vertex.find(j->get_id())->second++;
            }
        }
    }
    int min=1000;
    for (pair<int,int> i : count_vertex)
    {
        if (i.second<min)
        {
            min=i.second;
        }
    }
    if (min<=1)
    {
        return false;
    }
    return true;
}

Vertex* pick_random_neighbour(Vertex& vertex)
{
    int vertex_index = rand() % vertex.get_neighbours().size();
    return vertex.get_neighbours()[vertex_index];
}

bool cmp(Vertex* lhs, Vertex* rhs)
{
    return lhs->angle > rhs->angle;
}

// careful, this function is unsafe because we don't check the bounds
Vertex* pick_steepest_neighbour(Vertex& vertex,int lala)
{
    vector<Vertex*> neighbours=vertex.get_neighbours();

    for(Vertex * i : neighbours)
    {
        i->angle=atan(i->get_coords()[1]/i->get_coords()[2]);
    }
    
    sort(neighbours.begin(),neighbours.end(),cmp);

    if (lala>=neighbours.size())
    {
        cout<<"Bounds problem"<<endl;
        return neighbours.back();
    }
    else
    {
        return neighbours[lala];
    }
}



bool cmp_edge(pair<tuple<int,int>,vector<Tetrahedron*>>& lhs, pair<tuple<int,int>,vector<Tetrahedron*>>& rhs)
{
    return lhs.second.size()>rhs.second.size();
}

double fitness(map<tuple<int,int>,int> edge_to_vertex,vector<Tetrahedron>& tetra_list,map<tuple<int,int>,vector<Tetrahedron*>>& edge_dict)
{
    bool not_good;
    double fitness_var=0;
    for(pair<tuple<int,int>,int> i : edge_to_vertex)
    {
        if (is_cycle(edge_dict[i.first]))
        {
            not_good=false;
            for (Tetrahedron* j : edge_dict[i.first])
            {
                if (j->get_in_diamond()==true)
                {
                    not_good=true;
                    break;
                }
            }
        }
        else
        {
            not_good=true;
        }
        if (!not_good)
        {
            fitness_var++;
        }
    }
    return fitness_var;
}

// void apply(map<tuple<int,int>,int>& edge_to_vertex,map<tuple<int,int>,vector<Tetrahedron*>>& edge_dict)
// {

//     for(pair<tuple<int,int>,int> i : edge_to_vertex)
//     {
//        for (Tetrahedron* j : edge_dict[i.first])
//         {
//             j->set_in_diamond(true);
//         }
//     }
// }

// map<tuple<int,int>,vector<Vertex*>> step_1(vector<Vertex>& vertex_list,vector<Tetrahedron>& tetra_list,map<tuple<int,int>,vector<Tetrahedron*>>& edge_dict)
// {
//     map<tuple<int,int>,int> edge_to_vertex;
//     map<tuple<int,int>,vector<Vertex*>> lala;
   
//     double before_fitness=0;
//     double new_fitness=0;
//     bool new_elem=false;
//     for (int i=0;i<100000;i++)
//     {
//         new_elem=false;
//         auto it = edge_dict.begin();
//         std::advance(it, rand() % edge_dict.size());
//         tuple<int,int> random_key = it->first;
//         if (edge_to_vertex.count(random_key)==0)
//         {
//             new_elem=true;
//             edge_to_vertex[random_key]=0;
//             for (Tetrahedron* tetra : edge_dict[random_key])
//             {
//                 if ()
//             }
//         }
//         else
//         {
//             edge_to_vertex.erase(random_key);
//         }
//         new_fitness=fitness(edge_to_vertex,tetra_list,edge_dict);
//         // cout<<new_fitness<<endl;
//         if (new_fitness<before_fitness)
//         {
//             if (new_elem)
//             {
//                 edge_to_vertex.erase(random_key);
//             }
//             else
//             {
//                 edge_to_vertex.erase(random_key);
//             }
            
//         }
//         else
//         {
//             before_fitness=new_fitness;
//         }
        
//     }
//     cout<<new_fitness<<endl;
//     return lala;
// }



map<tuple<int,int>,vector<Vertex*>> step_1_edge_degree(vector<Vertex>& vertex_list,vector<Tetrahedron>& tetra_list,map<tuple<int,int>,vector<Tetrahedron*>>& edge_dict)
{
    vector<pair<tuple<int,int>,vector<Tetrahedron*>>> edge_dict_copy;
    map<tuple<int,int>,vector<Vertex*>> edge_to_vertex;
    map<int,int> vertex_check;
    bool already_matched;

    for (pair<tuple<int,int>,vector<Tetrahedron*>> i : edge_dict)
    {
        pair<tuple<int,int>,vector<Tetrahedron*>> tmp={i.first,i.second};
        edge_dict_copy.push_back(tmp);
    }
    
    sort(edge_dict_copy.begin(),edge_dict_copy.end(),cmp_edge);
    int count=0;
    pair<tuple<int,int>,vector<Tetrahedron*>> i;
    // cout<<"lala"<<edge_dict.end()->second.size()<<endl;
    for(pair<tuple<int,int>,vector<Tetrahedron*>> i : edge_dict_copy)
    {
        if (is_cycle(i.second))
        {
            already_matched=false;
            if (vertex_check.count(get<0>(i.first))==0)
            {
                for(Tetrahedron* tetra : i.second)
                {
                    if (tetra->get_in_diamond()==true)
                    {
                        already_matched=true;
                        break;
                    }
                }
                if (!already_matched)
                {
                    vector<Vertex*> tmp={&vertex_list[get<0>(i.first)]};
                    edge_to_vertex[i.first]=tmp;
                    for(Tetrahedron* tetra : i.second)
                    {
                        tetra->set_in_diamond(true);
                    }
                }
            }
            else if (vertex_check.count(get<1>(i.first))==0)
            {
                for(Tetrahedron* tetra : i.second)
                {
                    if (tetra->get_in_diamond()==true)
                    {
                        already_matched=true;
                        break;
                    }
                }
                if (!already_matched)
                {
                    vector<Vertex*> tmp={&vertex_list[get<1>(i.first)]};
                    edge_to_vertex[i.first]=tmp;
                    for(Tetrahedron* tetra : i.second)
                    {
                        tetra->set_in_diamond(true);
                    }
                }
            }
        }
    }
    return edge_to_vertex;
}


map<tuple<int,int>,vector<Vertex*>> step_1_bfs(vector<Vertex>& vertex_list,vector<Tetrahedron>& tetra_list,map<tuple<int,int>,vector<Tetrahedron*>>& edge_dict)
{
    map<tuple<int,int>,vector<Vertex*>> edge_to_vertex;
    map<tuple<int,int>,vector<Tetrahedron*>> diamond_list;
    unordered_set<int> lala;
    queue<Tetrahedron*> wait_list;
    wait_list.push(&tetra_list[0]);
    double count=0;
    while(!wait_list.empty())
    {
        Tetrahedron* tetra=wait_list.front();
        wait_list.pop();
        if (lala.count(tetra->get_id())==0)
        {
            lala.insert(tetra->get_id());
            for (tuple<int,int> edge : tetra->enumerate_edges())
            {
                if (diamond_list.count(edge)==0)
                {
                    if(is_cycle(edge_dict[edge]))
                    {
                        if (count_if(edge_dict[edge].begin(),edge_dict[edge].end(),[](Tetrahedron* i){return i->get_in_diamond();})==0)
                        {
                            diamond_list[edge]=edge_dict[edge];
                            for (Tetrahedron* tmp : edge_dict[edge])
                            {
                                tmp->set_in_diamond(true);
                                count++;
                            }
                        }
                    }
                }
                
                for (Tetrahedron* tmp2 : edge_dict[edge])
                {
                    wait_list.push(tmp2);
                }   
            }
            wait_list.pop();
        }
    }
    cout<<count/tetra_list.size()<<endl;
    cout<<lala.size()<<endl;

    count=0;
    // for (pair<tuple<int,int>,vector<Tetrahedron*>> tetra : diamond_list)
    // {
    //     for (Tetrahedron* i : tetra.second)
    //     {
    //         count+=i->get_is_on_boundary();
    //     }   
    // }
    for (Tetrahedron i : tetra_list)
    {
        count+=1-i.get_in_diamond();
    }  
    cout<<count/tetra_list.size()<<endl;
    return edge_to_vertex;
}


map<tuple<int,int>,vector<Vertex*>> step_1_vertex_choose_neighbour(vector<Vertex>& vertex_list,vector<Tetrahedron>& tetra_list,map<tuple<int,int>,vector<Tetrahedron*>>& edge_dict)
{
    map<tuple<int,int>,vector<Vertex*>> edge_to_vertex;
    for(int i=0;i<vertex_list.size();i++)
    {
        tuple<int,int> tmp;
        int lala=0;
        do
        {
            // Vertex* v2 =pick_random_neighbour(vertex_list[i]);
            Vertex* v2 =pick_steepest_neighbour(vertex_list[i],lala);

            if (vertex_list[i].get_id()<v2->get_id())
            {
                tmp= make_tuple(vertex_list[i].get_id(),v2->get_id());
            }
            else
            {
                tmp= make_tuple(v2->get_id(),vertex_list[i].get_id());
            }
            lala++;
        } while (edge_to_vertex.count(tmp)!=0 and lala<=vertex_list[i].get_neighbours().size());
        vector<Vertex*> vec_tmp={&vertex_list[i]};
        edge_to_vertex.insert({tmp,vec_tmp});
    }
    return edge_to_vertex;
}