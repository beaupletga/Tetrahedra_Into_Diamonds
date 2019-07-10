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

int vertex_degree(vector<Diamond> &diamond_list,int id)
{
    unordered_set<int> diamond_ids;
    stack<Next> stack_face;
    int total_degree=0;
    for (int i=0;i<diamond_list.size();i++)
    {
        if (diamond_list[i].has_anchor && diamond_list[i].get_anchor_vertex()->get_id()==id)// && diamond_list[i].get_tetra_list().size()>1)
        {
            Next first;
            first.from=&diamond_list[i];
            first.to=diamond_list[i].get_neighbours()[0];
            first.from_face_index=0;
            if (diamond_list[i].get_tetra_list().size()==1)
            {
                first.from_face_index=1;
                first.last_index=0;
                first.to=diamond_list[i].get_neighbours()[1];
            }
            else
            {
                first.last_index=2;
            }          
            
            if (first.to==NULL)
            {
                if (diamond_list[i].get_tetra_list().size()>1)
                {
                    for(int j=0;j<diamond_list[i].get_neighbours().size();j+=2)
                    {
                        if (diamond_list[i].get_neighbours()[j]!=NULL)
                        {
                            // cout<<"mama "<<(diamond_list[i].get_neighbours()[j]!=NULL)<<" "<<j<<endl;
                            first.to=diamond_list[i].get_neighbours()[j];
                            first.from_face_index=j;    
                            break;
                        }
                    }   
                }
                else
                {
                    if (diamond_list[i].get_neighbours()[2]!=NULL)
                    {
                        first.to=diamond_list[i].get_neighbours()[2];
                        first.from_face_index=2;   
                    }
                    if (diamond_list[i].get_neighbours()[3]!=NULL)
                    {
                        first.to=diamond_list[i].get_neighbours()[3];
                        first.from_face_index=3;  
                    }
                }                             
            }

            if (first.to==NULL)
            {
                return diamond_list[i].get_tetra_list().size();
            }
            // cout<<"face "<< first.from_face_index<<" "<<diamond_list[i].get_tetra_list().size()<<endl;
            // cout<<(diamond_list[i].get_neighbours()[first.from_face_index]==NULL)<<endl;
            // display_face(diamond_list[i].neighbours_faces[first.from_face_index]);
            stack_face.push(first);
            break;
        }
    }
    while (!stack_face.empty())
    {
        Next current = stack_face.top();
        stack_face.pop();
        if (current.to!=NULL && diamond_ids.count(current.to->get_id())==0)
        {
            diamond_ids.insert(current.to->get_id());
            // total_degree+=current.to->get_tetra_list().size();
        }
        else
        {
            continue;
        }
        // cout<<"x1"<<endl;
        // display_face(current.from->neighbours_faces[current.from_face_index]);
        // cout<<current.from->has_anchor<<" "<<current.from->get_anchor_vertex()->get_id()<<endl;
        // current.from->display_vertices_id();
        // current.to->display_vertices_id();
        int neighbour_face_size = current.to->get_neighbours().size();
        int neighbour_face_index = -1;
        // cout<<"x2"<<endl;
        for (int k=0;k<current.to->neighbours_faces.size();k++)
        {
            if (current.to->neighbours_faces[k]==current.from->neighbours_faces[current.from_face_index])
            {
                neighbour_face_index=k;
                break;
            }
        }
        // cout<<"x3"<<endl;
        if (neighbour_face_index==-1)
        {
            cout<<"unknown face"<<endl;
            assert(true==false);
        }

        if (current.to->get_tetra_list().size()>1)
        {
            // cout<<"x4"<<endl;
            if (current.from->get_permutation(current.from_face_index)[0]==current.last_index)
            {
                vector<int> indexes;
                if (neighbour_face_index%2==0)
                {
                    int a = (neighbour_face_size+(neighbour_face_index+1)%neighbour_face_size)%neighbour_face_size;
                    int b = (neighbour_face_size+(neighbour_face_index-1)%neighbour_face_size)%neighbour_face_size;
                    int c =(neighbour_face_size+(neighbour_face_index-2)%neighbour_face_size)%neighbour_face_size ;

                    indexes = {a,b,c};
                }
                else
                {
                    int a = (neighbour_face_size+(neighbour_face_index-1)%neighbour_face_size)%neighbour_face_size;
                    int b = (neighbour_face_size+(neighbour_face_index-2)%neighbour_face_size)%neighbour_face_size;
                    int c =(neighbour_face_size+(neighbour_face_index-3)%neighbour_face_size)%neighbour_face_size ;

                    indexes = {a,b,c};
                }
                total_degree+=2;
                
                // cout<<neighbour_face_index<<" "<<(neighbour_face_size+(neighbour_face_index-2)%neighbour_face_size)%neighbour_face_size<<endl;
                // cout<<indexes[0]<<" "<<indexes[1]<<" "<<indexes[2]<<endl;
                // cout<<"0"<<endl;
                // display_face(current.to->neighbours_faces[indexes[0]]);
                // display_face(current.to->neighbours_faces[indexes[1]]);
                // display_face(current.to->neighbours_faces[indexes[2]]);
                
                if (current.to->neighbours_faces[indexes[0]]!=tuple<int,int,int>{0,0,0})
                {
                    Next next0;
                    next0.from=current.to;
                    next0.to=current.to->get_neighbours()[indexes[0]];
                    next0.from_face_index=indexes[0];
                    next0.last_index=0;
                    stack_face.push(next0);
                }
                if (current.to->neighbours_faces[indexes[1]]!=tuple<int,int,int>{0,0,0})
                {
                    Next next1;
                    next1.from=current.to;
                    next1.to=current.to->get_neighbours()[indexes[1]];
                    next1.from_face_index=indexes[1];
                    next1.last_index=1;
                    stack_face.push(next1);
                }
                if (current.to->neighbours_faces[indexes[2]]!=tuple<int,int,int>{0,0,0})
                {
                    Next next2;
                    next2.from=current.to;
                    next2.to=current.to->get_neighbours()[indexes[2]];
                    next2.from_face_index=indexes[2];
                    next2.last_index=1;
                    stack_face.push(next2);
                }
            }
            if (current.from->get_permutation(current.from_face_index)[1]==current.last_index)
            {
                vector<int> indexes;
                if (neighbour_face_index%2==0)
                {
                    int a = (neighbour_face_size+(neighbour_face_index+1)%neighbour_face_size)%neighbour_face_size;
                    int b = (neighbour_face_size+(neighbour_face_index+2)%neighbour_face_size)%neighbour_face_size;
                    int c =(neighbour_face_size+(neighbour_face_index+3)%neighbour_face_size)%neighbour_face_size ;

                    indexes = {a,b,c};
                    // indexes = {neighbour_face_index+1,(neighbour_face_index+2)%neighbour_face_size,
                    // (neighbour_face_index+3)%neighbour_face_size};
                }
                else
                {
                    int a = (neighbour_face_size+(neighbour_face_index-1)%neighbour_face_size)%neighbour_face_size;
                    int b = (neighbour_face_size+(neighbour_face_index+1)%neighbour_face_size)%neighbour_face_size;
                    int c =(neighbour_face_size+(neighbour_face_index+2)%neighbour_face_size)%neighbour_face_size ;

                    indexes = {a,b,c};
                    // indexes = {neighbour_face_index-1,(neighbour_face_index+1)%neighbour_face_size,
                    // (neighbour_face_index+2)%neighbour_face_size};
                }



                total_degree+=2;
                // cout<<"1"<<endl;
                // display_face(current.to->neighbours_faces[indexes[0]]);
                // display_face(current.to->neighbours_faces[indexes[1]]);
                // display_face(current.to->neighbours_faces[indexes[2]]);
                
                if (current.to->neighbours_faces[indexes[0]]!=tuple<int,int,int>{0,0,0})
                {
                    Next next0;
                    next0.from=current.to;
                    next0.to=current.to->get_neighbours()[indexes[0]];
                    next0.from_face_index=indexes[0];
                    next0.last_index=1;
                    stack_face.push(next0);
                }
                if (current.to->neighbours_faces[indexes[1]]!=tuple<int,int,int>{0,0,0})
                {
                    Next next1;
                    next1.from=current.to;
                    next1.to=current.to->get_neighbours()[indexes[1]];
                    next1.from_face_index=indexes[1];
                    next1.last_index=0;
                    stack_face.push(next1);
                }
                if (current.to->neighbours_faces[indexes[2]]!=tuple<int,int,int>{0,0,0})
                {
                    Next next2;
                    next2.from=current.to;
                    next2.to=current.to->get_neighbours()[indexes[2]];
                    next2.from_face_index=indexes[2];
                    next2.last_index=0;
                    stack_face.push(next2);
                }
                
            }
            if (current.from->get_permutation(current.from_face_index)[2]==current.last_index)
            {
                int start;
                if (neighbour_face_index%2==0)
                {
                    start=0;
                }
                else
                {
                    start=1;
                }
                // cout<<"2"<<endl;
                // for (int i : current.to->get_vertex_order())
                // {
                //     cout<<i<<" ";
                // }
                // cout<<endl;
                for (int i=start;i<current.to->get_neighbours().size();i+=2)
                {
                    total_degree+=1;
                    if (current.to->neighbours_faces[i]!=tuple<int,int,int>{0,0,0})
                    {
                        // display_face(current.to->neighbours_faces[i]);
                        Next next;
                        next.from=current.to;
                        next.to=current.to->get_neighbours()[i];
                        next.from_face_index=i;
                        next.last_index=2;
                        stack_face.push(next);
                    }
                }
            }
        }
        else
        {
            total_degree+=1;

            vector<vector<int>> x = {{1,2,3},{0,2,3},{0,1,3},{0,1,2}};

            vector<int> indexes;
            if (neighbour_face_index==0)
            {
                indexes={1,2,3};
            }
            if (neighbour_face_index==1)
            {
                indexes={0,2,3};
            }
            if (neighbour_face_index==2)
            {
                indexes={0,1,3};
            }
            if (neighbour_face_index==3)
            {
                indexes={0,1,2};
            }

            // cout<<"Careful"<<endl;
            // cout<<current.from->get_permutation(current.from_face_index)[0]<<" "<<current.from->get_permutation(current.from_face_index)[1]<<" "<<current.from->get_permutation(current.from_face_index)[2]<<endl;
            // cout<<current.last_index<<" "<<neighbour_face_index<<endl;
            // display_face(current.to->neighbours_faces[0]);
            // display_face(current.to->neighbours_faces[1]);
            // display_face(current.to->neighbours_faces[2]);
            // display_face(current.to->neighbours_faces[3]);
            // cout<<endl;

            int which_case;
            if (current.from->get_permutation(current.from_face_index)[0]==current.last_index)
            {
                which_case = x[neighbour_face_index][0];
            }
            if (current.from->get_permutation(current.from_face_index)[1]==current.last_index)
            {
                which_case = x[neighbour_face_index][1];
            }
            if (current.from->get_permutation(current.from_face_index)[2]==current.last_index)
            {
                which_case = x[neighbour_face_index][2];
            }

            for (int i=0;i<3;i++)
            {
                if (current.from->get_permutation(current.from_face_index)[i]!=current.last_index)
                {
                    Next next0;
                    next0.from=current.to;
                    next0.to=current.to->get_neighbours()[indexes[i]];
                    next0.from_face_index=indexes[i];

                    if (x[indexes[i]][0]==which_case)
                    {
                        next0.last_index=0;
                    }
                    if (x[indexes[i]][1]==which_case)
                    {
                        next0.last_index=1;
                    }   
                    if (x[indexes[i]][2]==which_case)
                    {
                        next0.last_index=2;
                    }

                    stack_face.push(next0);
                    // cout<<"vertice "<<current.to->vertex_order[indexes[i]]<<endl;
                    // display_face(current.to->neighbours_faces[indexes[i]]);
                }
            }
            // cout<<"end"<<endl;
        }
        
        // sleep(1);
    }
    return total_degree;
}