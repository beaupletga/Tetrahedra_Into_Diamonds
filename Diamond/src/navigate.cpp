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


vector<int> BFS(int diamond_array[],bool diamond_extra_bytes_array[],int array_size,map<int,int> &index_to_diamond_id)
{
    vector<int> path;
    queue<int> wait_list;
    unordered_set<int> lala;
    // wait_list.push(0);
    int q=0;

    for(auto [key,val] : index_to_diamond_id)
    {
        if (val==100)
        {
            wait_list.push(key);
            break;
        }
    }

    while(!wait_list.empty())
    {
        int index = wait_list.front();
        wait_list.pop();
        int i=index+1;
        // int diamond_id = index_to_diamond(diamond_extra_bytes_array,array_size,index);
        int diamond_id = index_to_diamond_id[index];
        if(lala.count(diamond_id)==0)
        {
            lala.insert(diamond_id);
            path.push_back(diamond_id);
            while(diamond_extra_bytes_array[i]!=1 && i<array_size)
            {
                if (diamond_array[i]!=-1)
                {
                    wait_list.push(diamond_array[i]);
                }
                i++;               
            }
            i=index;
            while(diamond_extra_bytes_array[i]!=1 && i<array_size)
            {
                if (diamond_array[i]!=-1)
                {
                    wait_list.push(diamond_array[i]);
                }
                i--;
            }
            if (diamond_array[i]!=-1)
            {
                wait_list.push(diamond_array[i]);
            }
            q++;            
        }
        
        if (q==500){
            break;
        }
    }
    return path;
}


