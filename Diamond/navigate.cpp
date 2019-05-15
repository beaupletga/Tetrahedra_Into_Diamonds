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