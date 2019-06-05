#include "../include/step4.h"


// this function reads all diamond and create the adjacency array
// this is an array containing the index of the neighbour for each face of each diamond
// ex : at index 2, there is the index of the neighbour (this index is more precise as it's
// the index of the face of the neighboring diamond) sharing the third face of the first diamond
map<int,int> step_4(vector<Tetrahedron> &tetra_list,vector<Diamond> &diamond_list,int (tetra_array)[],
int (diamond_array)[],bool (diamond_extra_bytes_array)[],int diamond_array_size)
{
  
    map<int,int> diamond_id_to_index;
    map<int,int> index_to_diamond_id;
    int index=0;
    // each diamond is represented by an id and the index of the first face in the diamond array
    for(int i=0;i<diamond_list.size();i++)
    {
        diamond_id_to_index[diamond_list[i].get_id()]=index;
        index+=diamond_list[i].get_neighbours().size();
    }

    index=0;
    // for each face, we assign the index of the diamond (first face)
    for(int i=0;i<diamond_list.size();i++)
    {
        diamond_extra_bytes_array[index]=1;
        for(Diamond* &diamond : diamond_list[i].get_neighbours())
        {
            if (diamond==NULL)
            {
                diamond_array[index]=-1;
            }
            else
            {
                // offset=0 => first face of the tetra...
                int offset = diamond->get_neighbour_index(&diamond_list[i]);
                diamond_array[index]=diamond_id_to_index[diamond->get_id()]+offset;
            }
            index_to_diamond_id[index]=diamond_list[i].get_id();
            index++;
        }
    }

    for(int i=0;i<tetra_list.size();i+=2)
    {
        tetra_array[i]=diamond_id_to_index[tetra_list[i].get_diamond_ref()->get_id()]+tetra_list[i].get_position_in_diamond();
    }
    return index_to_diamond_id;
}
