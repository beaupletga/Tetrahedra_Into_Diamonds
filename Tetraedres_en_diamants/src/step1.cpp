#include "../include/step1.h"

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
            count_vertex[j->get_id()]+=1;
        }
    }
    for (pair<int,int> i : count_vertex)
    {
        if (i.second<2)
        {
            return false;
        }
    }
    return true;
}

// iterate over the tetrahedra in order to form diamonds
// return a dict of central edges and the corresponding tetrahedra
map<tuple<int,int>,vector<Tetrahedron*>> step_1_bfs(vector<Vertex>& vertex_list,vector<Tetrahedron>& tetra_list,map<tuple<int,int>,vector<Tetrahedron*>>& edge_dict)
{
    map<tuple<int,int>,vector<Tetrahedron*>> diamond_list;
    unordered_set<int> visited_tetra;
    queue<Tetrahedron*> wait_list;
    vector<tuple<int,int,int>> ocurrences;

    int first_tetra_index=rand()%tetra_list.size();
    wait_list.push(&tetra_list[first_tetra_index]);
    while(!wait_list.empty())
    {
        // add top tetrahedron
        Tetrahedron* tetra=wait_list.front();
        wait_list.pop();
        // if we haven't go trough it yet
        if (visited_tetra.count(tetra->get_id())==0)
        {
            visited_tetra.insert(tetra->get_id());
            // enumerate the 6 edges of the treta to get the adjacents tetra
            ocurrences.clear();
            for (tuple<int,int> edge : tetra->enumerate_edges())
            {
                // if we haven't already took this edge to form a diamond
                if (diamond_list.count(edge)==0 && edge_dict[edge].size()<=9)
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
    return diamond_list;
}
