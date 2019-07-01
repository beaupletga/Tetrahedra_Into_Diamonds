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

struct Next
{
    Diamond* from;
    Diamond* to;
    int from_face_index;
    int last_index;
};


void display_face(tuple<int,int,int> face)
{
    cout<<get<0>(face)<<" "<<get<1>(face)<<" "<<get<2>(face)<<endl;
}

void vertex_degree(vector<Diamond> &diamond_list,int id)
{
    unordered_set<int> diamond_ids;
    stack<Next> stack_face;
    for (int i=0;i<diamond_list.size();i++)
    {
        if (diamond_list[i].get_anchor_vertex()->get_id()==id && diamond_list[i].has_anchor)
        {
            for(auto j : diamond_list[i].get_vertex_order())
            {
                cout<<j<<" ";
            }
            cout<<endl;

            cout<<"a"<<endl;
            Next first;
            first.from=&diamond_list[i];
            first.to=diamond_list[i].get_neighbours()[0];
            first.from_face_index=0;
            first.last_index=2;

            if (first.to==NULL)
            {
                cout<<"pas de chance"<<endl;
                assert(true==false);
            }
            cout<<"b"<<endl;
            stack_face.push(first);
            while (!stack_face.empty())
            {
                cout<<stack_face.size()<<endl;
                cout<<"c"<<endl;
                
                Next tmp = stack_face.top();
                stack_face.pop();
                // display_face(tmp.from->neighbours_faces[tmp.from_face_index]);
                int j=-1;
                for (int k=0;k<tmp.to->neighbours_faces.size();k++)
                {
                    if (tmp.to->neighbours_faces[k]==tmp.from->neighbours_faces[tmp.from_face_index])
                    {
                        display_face(tmp.to->neighbours_faces[k]);
                        j=k;
                    }
                }
                if (j==-1)
                {
                    assert(true==false);
                }
                // display_face(tmp.to->neighbours_faces[j]);
                if (tmp.to->get_tetra_list().size()>1)
                {
                    cout<<"d"<<endl;
                    cout<<"last index : "<<tmp.last_index<<endl;
                    if (tmp.from->get_permutation(j)[0]==tmp.last_index)
                    {
                        cout<<"e"<<endl;
                        Next a;
                        Next b;
                        Next c;

                        a.from=tmp.to;
                        b.from=tmp.to;
                        c.from=tmp.to;
                        a.last_index=0;
                        b.last_index=0;
                        c.last_index=0;
                        // a.from_face_index=j;
                        // b.from_face_index=j;
                        // c.from_face_index=j;


                        if (j%2==0)
                        {
                            cout<<"e1"<<endl;
                            a.to=tmp.to->get_neighbours()[(j+1)%tmp.to->get_neighbours().size()];
                            b.to=tmp.to->get_neighbours()[(j-1)%tmp.to->get_neighbours().size()];
                            c.to=tmp.to->get_neighbours()[(j-2)%tmp.to->get_neighbours().size()];
                            a.from_face_index=(j+1)%tmp.to->get_neighbours().size();
                            b.from_face_index=(j-1)%tmp.to->get_neighbours().size();
                            c.from_face_index=(j-2)%tmp.to->get_neighbours().size();

                            display_face(tmp.to->neighbours_faces[(j+1)%tmp.to->get_neighbours().size()]);
                            display_face(tmp.to->neighbours_faces[(j-1)%tmp.to->get_neighbours().size()]);
                            display_face(tmp.to->neighbours_faces[(j-2)%tmp.to->get_neighbours().size()]);
                        }
                        else
                        {
                            cout<<"e2"<<endl;
                            a.to=tmp.to->get_neighbours()[(j-1)%tmp.to->get_neighbours().size()];
                            b.to=tmp.to->get_neighbours()[(j-2)%tmp.to->get_neighbours().size()];
                            c.to=tmp.to->get_neighbours()[(j-3)%tmp.to->get_neighbours().size()];
                            a.from_face_index=(j-1)%tmp.to->get_neighbours().size();
                            b.from_face_index=(j-2)%tmp.to->get_neighbours().size();
                            c.from_face_index=(j-3)%tmp.to->get_neighbours().size();

                            display_face(tmp.to->neighbours_faces[(j-1)%tmp.to->get_neighbours().size()]);
                            display_face(tmp.to->neighbours_faces[(j-2)%tmp.to->get_neighbours().size()]);
                            display_face(tmp.to->neighbours_faces[(j-3)%tmp.to->get_neighbours().size()]);
                        }
                        
                        stack_face.push(a);
                        stack_face.push(b);
                        stack_face.push(c);
                    }
                    else if (tmp.from->get_permutation(j)[1]==tmp.last_index)
                    {
                        cout<<"f"<<endl;
                        Next a;
                        Next b;
                        Next c;

                        a.from=tmp.to;
                        b.from=tmp.to;
                        c.from=tmp.to;
                        a.last_index=1;
                        b.last_index=1;
                        c.last_index=1;
                        // a.from_face_index=j;
                        // b.from_face_index=j;
                        // c.from_face_index=j;

                        if (j%2==0)
                        {
                            cout<<"f1"<<endl;
                            a.to=tmp.to->get_neighbours()[j+1];
                            b.to=tmp.to->get_neighbours()[(j-1)%tmp.to->get_neighbours().size()];
                            c.to=tmp.to->get_neighbours()[(j-2)%tmp.to->get_neighbours().size()];
                            a.from_face_index=(j+1)%tmp.to->get_neighbours().size();
                            b.from_face_index=(j-1)%tmp.to->get_neighbours().size();
                            c.from_face_index=(j-2)%tmp.to->get_neighbours().size();

                            display_face(tmp.to->neighbours_faces[(j+1)%tmp.to->get_neighbours().size()]);
                            display_face(tmp.to->neighbours_faces[(j-1)%tmp.to->get_neighbours().size()]);
                            display_face(tmp.to->neighbours_faces[(j-2)%tmp.to->get_neighbours().size()]);
                        }
                        else
                        {
                            cout<<"f2"<<endl;
                            a.to=tmp.to->get_neighbours()[(j-1)%tmp.to->get_neighbours().size()];
                            b.to=tmp.to->get_neighbours()[(j+1)%tmp.to->get_neighbours().size()];
                            c.to=tmp.to->get_neighbours()[(j+2)%tmp.to->get_neighbours().size()];
                            a.from_face_index=(j-1)%tmp.to->get_neighbours().size();
                            b.from_face_index=(j+1)%tmp.to->get_neighbours().size();
                            c.from_face_index=(j+2)%tmp.to->get_neighbours().size();

                            display_face(tmp.to->neighbours_faces[(j-1)%tmp.to->get_neighbours().size()]);
                            display_face(tmp.to->neighbours_faces[(j+1)%tmp.to->get_neighbours().size()]);
                            display_face(tmp.to->neighbours_faces[(j+2)%tmp.to->get_neighbours().size()]);
                            cout<<endl;
                            // display_face(tmp.to->neighbours_faces[(j+1)%tmp.to->get_neighbours().size()]);
                            // display_face(tmp.to->neighbours_faces[(j-1)%tmp.to->get_neighbours().size()]);
                            // display_face(tmp.to->neighbours_faces[(j-2)%tmp.to->get_neighbours().size()]);
                            // display_face(tmp.to->neighbours_faces[(j-3)%tmp.to->get_neighbours().size()]);

                        }

                        stack_face.push(a);
                        stack_face.push(b);
                        stack_face.push(c);
                    }
                    else if (tmp.from->get_permutation(j)[2]==tmp.last_index)
                    {
                        cout<<"g"<<endl;
                    }
                    // break;
                }
                else if (tmp.to->get_tetra_list().size()==1)
                {
                    if (tmp.to->get_permutation(j)[0]==tmp.last_index)
                    {
                        cout<<"h"<<endl;
                    }
                    else if (tmp.to->get_permutation(j)[1]==tmp.last_index)
                    {
                        cout<<"i"<<endl;
                    }
                    else if (tmp.to->get_permutation(j)[2]==tmp.last_index)
                    {
                        cout<<"j"<<endl;
                    }
                    
                }
                sleep(2);
            }
            break;
        }
    }
}