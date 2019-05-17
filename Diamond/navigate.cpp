#include "navigate.h"

// this function doesn't work with isolated tetra
int next_tetrahedron(int diamond_array[],int tetra_array[],bool diamond_extra_bytes_aray[],int tetra_index)
{
    if(tetra_index%2==0 && diamond_extra_bytes_aray[tetra_index+2]==0)
    {
        return tetra_index+2;        
    }
    else if(tetra_index%2==1 && diamond_extra_bytes_aray[tetra_index+1]==0)
    {
        return tetra_index+1;     
    }
    int i=tetra_index;
    while (diamond_extra_bytes_aray[i]!=1)
    {
        i--;
    }
    return i;
}

// this function doesn't work with isolated tetra
int previous_tetrahedron(int diamond_array[],int tetra_array[],bool diamond_extra_bytes_aray[],int tetra_index)
{
    if(tetra_index%2==0 && diamond_extra_bytes_aray[tetra_index-2]==0)
    {
        return tetra_index-2;        
    }
    else if(tetra_index%2==1 && diamond_extra_bytes_aray[tetra_index-1]==0)
    {
        return tetra_index-1;     
    }
    else//if(diamond_extra_bytes_aray[tetra_index]==1 || diamond_extra_bytes_aray[tetra_index-1]==1)
    {
        int i=tetra_index;
        while (diamond_extra_bytes_aray[i]!=1)
        {
            i++;
        }
        return i-2;
    }
}


vector<int> BFS(map<int,int> &index_to_diamond_id,int diamond_array[],bool diamond_extra_bytes_array[],
int array_size)
{
    vector<int> path;
    queue<int> wait_list;
    unordered_set<int> lala;
    wait_list.push(0);
    int w=0;
    // int q=0;
    while(!wait_list.empty())
    {
        int index = wait_list.front();
        wait_list.pop();
        int i=index+1;
        if(lala.count(index_to_diamond_id[index])==0)
        {
            w=0;
            wait_list.push(diamond_array[index]);
            lala.insert(index_to_diamond_id[index]);
            path.push_back(index_to_diamond_id[index]);
            // cout<<diamond_extra_bytes_array[index]<<endl;
            while(diamond_extra_bytes_array[i]!=1 && i<array_size)
            {
                if (diamond_array[i]!=-1)
                {
                    // cout<<index_to_diamond_id[diamond_array[i]]<<endl;
                    wait_list.push(diamond_array[i]);
                }
                i++;
                w++;
            }
            i=index;
            while(diamond_extra_bytes_array[i]!=1 && i<array_size)
            {
                if (diamond_array[i]!=-1)
                {
                    // cout<<index_to_diamond_id[diamond_array[i]]<<endl;
                    wait_list.push(diamond_array[i]);
                }
                i--;
                w++;
            }
            wait_list.push(diamond_array[i]);
            w++;
            // cout<<w<<endl;
            
        }
        // q++;
        // if (q==100){
        //     break;
        // }
    }
    return path;
}


