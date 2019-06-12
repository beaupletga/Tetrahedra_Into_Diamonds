#include "../include/step4.h"


int id_to_index(vector<Diamond> &diamond_list,Diamond* ref)
{
    for(int i=0;i<diamond_list.size();i++)
    {
        if (&diamond_list[i]==ref)
            return i;
    }
    assert(true==false);
    return -1;
}


// this function reads all diamond and create the adjacency array
// this is an array containing the index of the neighbour for each face of each diamond
// ex : at index 2, there is the index of the neighbour (this index is more precise as it's
// the index of the face of the neighboring diamond) sharing the third face of the first diamond
map<int,int> step_4(vector<Tetrahedron> &tetra_list,vector<Diamond> &diamond_list,int (tetra_array)[],
int (diamond_array)[],bool (diamond_extra_bytes_array)[],int diamond_array_size,map<int,Diamond*>& anchor_dict)
{
    vector<int> tetra_order;
    map<int,int> diamond_id_to_index;
    map<int,int> index_to_diamond_id;
    int index=0;

    // cout<<anchor_dict.size()<<endl;
    // cout<<0<<endl;
    for(int i=0;i<anchor_dict.size();i++)
    {
        // cout<<anchor_dict[i]->get_id()<<endl;
        diamond_id_to_index[anchor_dict[i]->get_id()]=index;
        // cout<<"xx "<<anchor_dict[i]->get_neighbours().size()<<endl;
        index+=anchor_dict[i]->get_neighbours().size();
        tetra_order.push_back(id_to_index(diamond_list,anchor_dict[i]));
    }

    // cout<<0.1<<endl;
    // each diamond is represented by an id and the index of the first face in the diamond array
    for(int i=0;i<diamond_list.size();i++)
    {
        if(diamond_id_to_index.count(diamond_list[i].get_id())==0)
        {
            diamond_id_to_index[diamond_list[i].get_id()]=index;
            index+=diamond_list[i].get_neighbours().size();
            tetra_order.push_back(i);
        }   
    }
    cout<<"index : "<<index<<endl;


    index=0;
    // for each face, we assign the index of the diamond (first face)
    for(int i=0;i<tetra_order.size();i++)
    {
        diamond_extra_bytes_array[index]=1;
        for(Diamond* diamond : diamond_list[tetra_order[i]].get_neighbours())
        {
            if (diamond==NULL)
            {
                diamond_array[index]=-1;
            }
            else
            {
                // offset=0 => first face of the tetra...
                int offset = diamond->get_neighbour_index(&diamond_list[tetra_order[i]]);
                diamond_array[index]=diamond_id_to_index[diamond->get_id()]+offset;
            }
            index_to_diamond_id[index]=diamond_list[tetra_order[i]].get_id();
            index++;
        }
    }
    cout<<"index : "<<index<<endl;
    for(int i=0;i<tetra_list.size();i+=2)
    {
        tetra_array[i]=diamond_id_to_index[tetra_list[i].get_diamond_ref()->get_id()]+tetra_list[i].get_position_in_diamond();
    }
    return index_to_diamond_id;
}
