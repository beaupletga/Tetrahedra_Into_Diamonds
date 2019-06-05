#include "../include/navigate.h"

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

// get diamond id from index in the diamond array
int index_to_diamond(bool diamond_extra_bytes_array[],int array_size,int index)
{
    int count=0;
    for(int i=0;i<=index;i++)
    {
        if(diamond_extra_bytes_array[i]==1)
        {
            count++;
        }
    }
    // because diamond id starts at 0
    return count-1;
}


vector<int> BFS(int diamond_array[],bool diamond_extra_bytes_array[],int array_size)
{
    vector<int> path;
    queue<int> wait_list;
    unordered_set<int> lala={-1};
    wait_list.push(0);
    int w=0;
    int q=0;
    while(!wait_list.empty())
    {
        int index = wait_list.front();
        wait_list.pop();
        int i=index+1;
        int diamond_id = index_to_diamond(diamond_extra_bytes_array,array_size,index);
        if(lala.count(diamond_id)==0)
        {
            w=0;
            wait_list.push(diamond_array[index]);
            lala.insert(diamond_id);
            path.push_back(diamond_id);
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
        q++;
        if (q==1000){
            break;
        }
    }
    return path;
}


