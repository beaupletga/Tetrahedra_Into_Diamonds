#include "step1.h"

// This first step consist in gathering tetra into diamonds such that the number of isolated tetra is minimized
// A diamond is a set of tetra sharing an edge and forming a cycle around that edge
// At the end we wish to have a set of edge central edge foreach of these diamond (1 edge -> 1 diamond)
// and one vertex which serves as anchor for the diamond

// take a set of tetra which share an edge and return true if they form a full cycle (i.e diamond)
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

// to compare the angle for the steepest_neighbour_function
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

// function used for sorting the edges by number of adjacents tetra
bool cmp_edge(pair<tuple<int,int>,vector<Tetrahedron*>>& lhs, pair<tuple<int,int>,vector<Tetrahedron*>>& rhs)
{
    return lhs.second.size()>rhs.second.size();
}

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
    // wait_list.push(&tetra_list[1000]);
    int tmppp=rand()%tetra_list.size();
    wait_list.push(&tetra_list[tmppp]);
    cout<<"First tetra : "<<tmppp<<endl;
    double count=0;
    while(!wait_list.empty())
    {
        // add top tetrahedron
        Tetrahedron* tetra=wait_list.front();
        wait_list.pop();
        // if we haven't go trough it yet
        if (lala.count(tetra->get_id())==0)
        {
            lala.insert(tetra->get_id());
            // enumerate the 6 edges of the treta to get the adjacents tetra
            vector<tuple<int,int,int>> ocurrences;
            for (tuple<int,int> edge : tetra->enumerate_edges())
            {
                // if we haven't already took this edge to form a diamond
                if (diamond_list.count(edge)==0)
                {
                    // if the tetra around this edge create a diamond
                    if(is_cycle(edge_dict[edge]))
                    {
                        // if none of these tetra is already in a diamond
                        if (count_if(edge_dict[edge].begin(),edge_dict[edge].end(),[](Tetrahedron* i){return i->get_in_diamond();})==0)
                        {
                            // we add the edge into a list, with the nb of tetra associated
                            ocurrences.push_back({get<0>(edge),get<1>(edge),edge_dict[edge].size()});
                        }
                    }
                }
            }
            // we take the edge with maximum adjacent tetra
            if (ocurrences.size()>0)
            {
                tuple<int,int,int> max = *max_element( ocurrences.begin(), ocurrences.end(),
                             []( tuple<int,int,int> &a, tuple<int,int,int> &b )
                             {
                                 return get<2>(a) < get<2>(b);
                             } );
                tuple<int,int> edge={get<0>(max),get<1>(max)};
                diamond_list[edge]=edge_dict[edge];
                // and mark all the tetra of this new diamond
                for (Tetrahedron* tmp : edge_dict[edge])
                {
                    tmp->set_in_diamond(true);
                    count++;
                }
            }
            // we push into the queue all tetra adjacent (by an edge) to the focused tetra
            for (Tetrahedron* tmp2 : tetra->get_neighbours())
            {
                wait_list.push(tmp2);
            } 
            // we pop the current tetra
            wait_list.pop();
        }
    }
    // cout<<"lala size : "<<lala.size()<<endl;

    // the tuple are sorted by the id of the first vertex
    // so by always taking the first vertex as root, they won't be any conflict
    for (pair<tuple<int,int>,vector<Tetrahedron*>> i : diamond_list)
    {
        edge_to_vertex[i.first]={&vertex_list[get<0>(i.first)]};
    }

    // std::ofstream outfile;
    // outfile.open("scores.csv", ios::app);
    // double count_tetra_diamond=0;
    // for (int i=0;i<tetra_list.size();i++)
    // {
    //     count_tetra_diamond+=tetra_list[i].get_in_diamond();
    // }

    // tuple<double,double,double> bary = tetra_list[tmppp].get_barycenter();
    // outfile<<get<0>(bary);
    // outfile<<",";
    // outfile<<get<1>(bary);
    // outfile<<",";
    // outfile<<get<2>(bary);
    // outfile<<",";
    // outfile<<count_tetra_diamond/tetra_list.size();
    // outfile<<"\n";
    // outfile.close();
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
        for(Tetrahedron* tetra : edge_dict[tmp])
        {
            tetra->set_in_diamond(true);
        }
    }
    return edge_to_vertex;
}