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

void check_2(int (diamond_array)[],int diamond_array_size)
{
    for (int i=0;i<diamond_array_size;i++)
    {
        if (diamond_array[i]!=-1)
        {
            if (i!=diamond_array[diamond_array[i]])
            {
                cout<<i<<" "<<diamond_array[i]<<" "<<diamond_array[diamond_array[i]]<<endl;
                cout<<"error in bijective redirection"<<endl;
                assert(true==false);
            }
        }
    }
    cout<<"Check 2 done"<<endl;
}

// check if the diamonds are well formed
// i.e no vertex has degree<2
void check_3(vector<Diamond> &diamond_list)
{
    unordered_map<int,int> map;
    for (Diamond &diamond : diamond_list)
    {
        if (diamond.get_tetra_list().size()!=1)
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
                    cout<<i.second<<endl;
                    // assert(true==false);
                }
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


void check_5(vector<Diamond> &diamond_list)
{
    int error1=0;
    int error2=0;
    vector<int> v={0,0,0};
    for (Diamond &diamond : diamond_list)
    {
        int size = diamond.get_tetra_list().size();
        // if (diamond.get_tetra_list().size()==1)
        {
            for (int i=0;i<diamond.get_neighbours().size();i++)
            {
                if (diamond.get_neighbours()[i]!=NULL)// && diamond.get_neighbours()[i]->get_tetra_list().size()==1)
                {
                    int left,right,tip;
                    if (diamond.get_vertex_order().size()>4)
                    {
                        if (i%2==0)
                        {
                            left = diamond.get_vertex_order()[i/2];
                            right = diamond.get_vertex_order()[(i/2+1)%(size)];
                            tip = diamond.get_vertex_order()[size];
                        }
                        else
                        {
                            left = diamond.get_vertex_order()[(i-1)/2];
                            right = diamond.get_vertex_order()[((i-1)/2+1)%(size)];
                            tip = diamond.get_vertex_order()[size+1];
                        }
                    }
                    else
                    {
                        if (i==0)
                        {
                            left = diamond.get_vertex_order()[1];
                            right = diamond.get_vertex_order()[2];
                            tip = diamond.get_vertex_order()[3];
                        }
                        if (i==1)
                        {
                            left = diamond.get_vertex_order()[0];
                            right = diamond.get_vertex_order()[2];
                            tip = diamond.get_vertex_order()[3];
                        }
                        if (i==2)
                        {
                            left = diamond.get_vertex_order()[0];
                            right = diamond.get_vertex_order()[1];
                            tip = diamond.get_vertex_order()[3];
                        }
                        if (i==3)
                        {
                            left = diamond.get_vertex_order()[0];
                            right = diamond.get_vertex_order()[1];
                            tip = diamond.get_vertex_order()[2];
                        }
                    }
                    
                    
                    vector<int> focus={left,right,tip};
                    vector<int> neighbour;
                    // for (int i : diamond.get_neighbours()[i]->get_vertex_order())
                    for(int j=0;j<diamond.get_neighbours()[i]->get_vertex_order().size();j++)
                    {
                        int tmp = diamond.get_neighbours()[i]->get_vertex_order()[j];
                        if (tmp==left || tmp==right || tmp==tip)
                        {
                            neighbour.push_back(j);
                        }
                    }
                    if (neighbour.size()!=3)
                    {
                        cout<<"Wrong neighbour size"<<endl;
                        assert(true==false);
                    }
                    else
                    {
                        if (diamond.get_neighbours()[i]->get_vertex_order().size()>4)
                        {
                            if (neighbour[1]==diamond.get_neighbours()[i]->get_vertex_order().size()-3 && neighbour[0]==0)
                            {
                                neighbour[0]=diamond.get_neighbours()[i]->get_vertex_order()[neighbour[1]];
                                neighbour[1]=diamond.get_neighbours()[i]->get_vertex_order()[0];
                            }
                            else
                            {
                                neighbour[0]=diamond.get_neighbours()[i]->get_vertex_order()[neighbour[0]];
                                neighbour[1]=diamond.get_neighbours()[i]->get_vertex_order()[neighbour[1]];
                            }
                            neighbour[2]=diamond.get_neighbours()[i]->get_vertex_order()[neighbour[2]];
                        }
                        else
                        {
                            neighbour[0]=diamond.get_neighbours()[i]->get_vertex_order()[neighbour[0]];
                            neighbour[1]=diamond.get_neighbours()[i]->get_vertex_order()[neighbour[1]];
                            neighbour[2]=diamond.get_neighbours()[i]->get_vertex_order()[neighbour[2]];
                        }

                        int permut0 = diamond.get_permutation(i)[0];
                        int permut1 = diamond.get_permutation(i)[1];
                        int permut2 = diamond.get_permutation(i)[2];

                        if (focus[permut0]!=neighbour[0] || focus[permut1]!=neighbour[1] || focus[permut2]!=neighbour[2])
                        // if (!(focus[permut0]==left && neighbour[permut1]==right && neighbour[permut2]==tip))
                        {
                            cout<<diamond.get_id()<<" "<<diamond.get_neighbours()[i]->get_id()<<endl;
                            cout<<permut0<<" "<<permut1<<" "<<permut2<<endl;
                            cout<<"focus : "<<endl;
                            cout<<left<<endl;
                            cout<<right<<endl;
                            cout<<tip<<endl;
                            cout<<"neighbour :"<<endl;
                            cout<<neighbour[0]<<endl;
                            cout<<neighbour[1]<<endl;
                            cout<<neighbour[2]<<endl;
                            cout<<endl;
                            cout<<focus[permut0]<<endl;
                            cout<<focus[permut1]<<endl;
                            cout<<focus[permut2]<<endl;
                            cout<<"Wrong permutation"<<endl;
                            assert(true==false);
                        }
                        else
                        {
                            // cout<<"true"<<endl;
                        }
                        
                    }
                }
            }
        }
    }
}

void check_6(bool diamond_extra_bytes_array[],int array_size,int tetra_list_size)
{
    int x=0;
    int i=0;
    while(i<array_size)
    {   
        int tmp = diamond_size(diamond_extra_bytes_array,array_size,i);
        if (tmp==4)
        {
            x++;
        }
        else
        {
            x+=tmp/2;
        }
        i+=tmp;
    }
    if (x!=tetra_list_size)
    {
        cout<<"Wrong number of tetrahedron"<<endl;
        assert(true==false);
    }
}

