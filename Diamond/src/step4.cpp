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
int (diamond_array)[],bool (diamond_extra_bytes_array)[],int diamond_array_size,map<int,Diamond*> &anchor_dict
,vector<tuple<int,int,int>> &permutation_array,vector<tuple<int,int,int>> &face_array)
{
    cout<<1<<endl;
    cout<<anchor_dict[12560]<<endl;
    vector<int> tetra_order;
    map<int,int> diamond_id_to_index;
    map<int,int> index_to_diamond_id;
    int index=0;
    for(int i=0;i<anchor_dict.size();i++)
    {
        cout<<i<<" "<<anchor_dict[i]<<endl;
        cout<<"id "<<i<<" "<<anchor_dict[i]->get_id()<<endl;
        diamond_id_to_index[anchor_dict[i]->get_id()]=index;
        cout<<1.5<<endl;
        index+=anchor_dict[i]->get_neighbours().size();
        cout<<1.75<<endl;
        tetra_order.push_back(id_to_index(diamond_list,anchor_dict[i]));
        cout<<1.85<<endl;
    }
    cout<<2<<endl;
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
    cout<<3<<endl;
    index=0;
    // for each diamond
    for(int i=0;i<tetra_order.size();i++)
    {
        cout<<30<<endl;
        diamond_extra_bytes_array[index]=1;
        int j=0;
        // we iterate over the external faces (neighbours)
        cout<<31<<endl;
        for(Diamond* diamond : diamond_list[tetra_order[i]].get_neighbours())
        {
            // if (get<0>(face_array[index])==0 && get<1>(face_array[index])==0 && get<2>(face_array[index])==1)
            // {
            //     cout<<"PROBLEM3"<<endl;
            //     assert(true==false);
            // }
            // if the neigbour doesn'texist (the diamond is on the boundary)
            cout<<4<<endl;
            if (diamond==NULL)
            {
                diamond_array[index]=-1;
                tuple<int,int,int> tmp = {0,0,0};
                permutation_array.push_back(tmp);
            }
            // ow, we check what is the 
            else
            {
                cout<<5<<endl;
                // offset=0 => first face of the tetra...
                // int offset = diamond->get_neighbour_index(&diamond_list[tetra_order[i]]);
                int offset = -1;
                for (int k=0;k<diamond->neighbours_faces.size();k++)
                {
                    if (diamond->neighbours_faces[k]==diamond_list[tetra_order[i]].neighbours_faces[j])
                    {
                        offset=k;
                    }
                }
                if (offset==-1)
                {
                    cout<<"unknown face"<<endl;
                    assert(true==false);
                }
                diamond_array[index]=diamond_id_to_index[diamond->get_id()]+offset;
                diamond_array[diamond_id_to_index[diamond->get_id()]+offset]=index;
                tuple<int,int,int> permut = 
                {diamond_list[tetra_order[i]].get_permutation(j)[0],
                diamond_list[tetra_order[i]].get_permutation(j)[1],
                diamond_list[tetra_order[i]].get_permutation(j)[2]};
                // if (index==4)
                // {
                //     cout<<get<0>(face_array[index])<<" "<<get<1>(face_array[index])<<" "<<get<2>(face_array[index])<<endl;
                // } 
                permutation_array.push_back(permut);
                // permutation_array[index] = permut;
                // if (index==4)
                // {
                //     cout<<get<0>(face_array[index])<<" "<<get<1>(face_array[index])<<" "<<get<2>(face_array[index])<<endl;
                // }
                // cout<<6<<endl;
            }
            face_array.push_back(diamond_list[tetra_order[i]].neighbours_faces[j]);
            // face_array[index] = diamond_list[tetra_order[i]].neighbours_faces[j];
            // if ()

            // cout<<index<<" "<<get<0>(face_array[index])<<" "<<get<1>(face_array[index])<<" "<<get<2>(face_array[index])<<endl;
            // if (index==4)
            // {
            //     cout<<get<0>(face_array[index])<<" "<<get<1>(face_array[index])<<" "<<get<2>(face_array[index])<<endl;
            //     cout<<"because i=4"<<endl;
            //     // assert(true==false);
            // }
            cout<<7<<endl;
            index_to_diamond_id[index]=diamond_list[tetra_order[i]].get_id();
            index++;
            j++;
            cout<<8<<endl;
        }
        cout<<9<<endl;
    }
    // for (int i=0;i<face_array.size();i++)
    // {
    //     if ((get<0>(face_array[i])==0) && (get<1>(face_array[i])==0) && (get<2>(face_array[i])==1))
    //     {
    //         cout<<i<<endl;
    //         cout<<get<0>(face_array[i])<<" "<<get<1>(face_array[i])<<" "<<get<2>(face_array[i])<<endl;
    //         cout<<"PROBLEM4"<<endl;
    //         assert(true==false);
    //     }
    // }
    // cout<<"index : "<<index<<endl;
    // for(int i=0;i<tetra_list.size();i+=2)
    // {
    //     tetra_array[i]=diamond_id_to_index[tetra_list[i].get_diamond_ref()->get_id()]+tetra_list[i].get_position_in_diamond();
    // }
    cout<<91<<endl;
    return index_to_diamond_id;
}
