#include "../include/consistency.h"


// check that no diamond has 2 faces of the same tetra on the boundary
void check_1(vector<Diamond> &diamond_list)
{
    for (Diamond diamond : diamond_list)
    {
        if (diamond.get_tetra_list().size()>1)
        {
            diamond.get_vertex_order();
        }
    }
    cout<<"Check 1 done"<<endl;
}

void check_2(int (tetra_array)[],int (diamond_array)[],int diamond_array_size)
{
    for (int i=0;i<diamond_array_size;i++)
    {
        if (diamond_array[i]!=-1)
        {
            if (diamond_array[i]!=diamond_array[diamond_array[i]])
            {
                // error in bijective redirection
                assert(true==false);
            }
        }
    }
    cout<<"Check 2 done"<<endl;
}

void check_3(vector<Diamond> &diamond_list)
{
    unordered_map<int,int> map;
    for (Diamond &diamond : diamond_list)
    {
        for (Tetrahedron* tetra : diamond.get_tetra_list())
        {
            for (Vertex* vertex : tetra->get_vertices())
            {
                map[vertex->get_id()]+=1;
            }
        }
        for(pair<int,int> i : map)
        {
            if (i.second<2)
            {
                assert(true==false);
            }
        }
    }
    cout<<"Check 3 done"<<endl;
}

void check_4(vector<Diamond> &diamond_list)
{
    int error1=0;
    int error2=0;
    vector<int> v={0,0,0};
    for (Diamond &diamond : diamond_list)
    {
        for (int i=0;i<diamond.get_neighbours().size();i++)
        {
            if ((diamond.get_neighbours()[i]==NULL && diamond.get_permutation(i)!=v))
            {
                error1++;
            }
            else if ((diamond.get_neighbours()[i]!=NULL && diamond.get_permutation(i)==v))
            {
                error2++;
            }
        }
    }
    if (error1==0 && error2==0)
    {
        cout<<"Check 4 done"<<endl;
    }
    else
    {
        assert(true==false);
    }
    
}