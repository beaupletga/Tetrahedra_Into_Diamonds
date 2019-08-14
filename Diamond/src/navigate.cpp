#include "../include/navigate.h"

// return the size of a diamond from an index
// index is one of the faces of the targeted diamond
int diamond_size(bool diamond_extra_bytes_array[],int array_size,int index)
{
    int count = 1;
    int i=index+1;
    while (diamond_extra_bytes_array[i]!=1 && i<array_size)
    {
        // cout<<diamond_extra_bytes_array[i]<<endl;
        count++;
        i++;
    }
    i=index;
    while (diamond_extra_bytes_array[i]!=1)
    {
        // cout<<diamond_extra_bytes_array[i]<<endl;
        count++;
        i--;
    }
    return count;
}

// return the index of the first face of the targeted diamond
int get_starting_index(bool diamond_extra_bytes_array[],int index)
{
    int i=index;
    while(diamond_extra_bytes_array[i]!=1)
    {
        i--;
    }
    return i;
}

// return the index of the next diamond
int next_diamond(bool diamond_extra_bytes_array[],int array_size,int i)
{
    i++;
    while (diamond_extra_bytes_array[i]!=1 & i<array_size)
    {
        i++;
    }
    return i;
}

// return the index of the previous diamond
int previous_diamond(bool diamond_extra_bytes_array[],int array_size,int i)
{
    i--;
    while (diamond_extra_bytes_array[i]!=1 & i>0)
    {
        i--;
    }
    return i;
}

// return the index of the next tetrahedron
int next_tetrahedron(bool diamond_extra_bytes_array[],int array_size,int i)
{
    int size = diamond_size(diamond_extra_bytes_array,array_size,i);
    if (size==4)
    {
        return next_diamond(diamond_extra_bytes_array,array_size,i);
    }
    else
    {
        if (i%2==0 & i+2<array_size)
        {
            return i+2;
        }
        else if (i+1<array_size)
        {
            return i+1;
        }
        else
        {
            cout<<"There is no next tetrahedron"<<endl;
            assert(true==false);
        }
    }
}

// return the index of the previous tetrahedron
int previous_tetrahedron(bool diamond_extra_bytes_array[],int array_size,int i)
{
    int size = diamond_size(diamond_extra_bytes_array,array_size,i);
    if (size==4)
    {
        return previous_diamond(diamond_extra_bytes_array,array_size,i);
    }
    else
    {
        if (i%2==0 & i-2>0)
        {
            return i-2;
        }
        else if (i-1>0)
        {
            return i-1;
        }
        else
        {
            cout<<"There is no previous tetrahedron"<<endl;
            assert(true==false);
        }
    }
}

// return the index of the ith tetra
int ith_tetra(bool diamond_extra_bytes_array[],int array_size,int i)
{
    int index=0;
    for (int j=0;j<i;j++)
    {
        index = next_tetrahedron(diamond_extra_bytes_array,array_size,index);
    }
    return index;
}

// return the index of the ith diamond
int ith_diamond(bool diamond_extra_bytes_array[],int array_size,int i)
{
    int index=0;
    for (int j=0;j<i;j++)
    {
        index = next_diamond(diamond_extra_bytes_array,array_size,index);
    }
    return index;
}


void display_face(tuple<int,int,int> face)
{
    cout<<get<0>(face)<<" "<<get<1>(face)<<" "<<get<2>(face)<<endl;
}

void display_face_diamond(bool diamond_extra_bytes_array[],vector<tuple<int,int,int>>& face_array,int id)
{
    int i=1;
    int count=0;
    while (count<id)
    {
        if (diamond_extra_bytes_array[i]==1)
        {
            count++;
        }
        i++;
    }
    cout<<"starting index : "<<i-1<<endl;
    display_face(face_array[i-1]);
    while (diamond_extra_bytes_array[i]!=1)
    {
        display_face(face_array[i]);
        i++;
    }
    cout<<"end index : "<<i<<endl;
}

// get diamond id from index in the diamond array
int index_to_diamond_id(bool diamond_extra_bytes_array[],int diamond_array_size,int index)
{
    int count=0;
    for(int i=0;i<=index;i++)
    {
        if(diamond_extra_bytes_array[i]==1)
        {
            count++;
        }
        if (i>=diamond_array_size)
        {
            cout<<"No such diamond"<<endl;
            assert(true==false);
        }
    }
    // because diamond id starts at 0
    return count-1;
}

// get index from diamond id
int diamond_id_to_index(bool diamond_extra_bytes_array[],int diamond_array_size,int diamond_id)
{
    int i=1;
    int count=0;
    while(count<diamond_id)
    {
        if (diamond_extra_bytes_array[i]==1)
        {
            count++;
        }
        i++;
    }
    return i-1;
}

vector<int> BFS_full_structure(vector<Diamond> &diamond_list,int starting_diamond_index)
{
    vector<int> path;
    queue<Diamond*> wait_list;
    unordered_set<int> lala;
    int q=0;

    wait_list.push(&diamond_list[starting_diamond_index]);
    while(!wait_list.empty())
    {
        // cout<<2<<endl;
        Diamond* index = wait_list.front();
        wait_list.pop();
        if (index==NULL)
        {
            continue;
        }
        int diamond_id = index->get_id();
        if(lala.count(diamond_id)==0)
        {
            lala.insert(diamond_id);
            path.push_back(diamond_id);
            for (int i=0;i<index->get_neighbours().size();i++)
            {
                wait_list.push(index->get_neighbours()[i]);
            }
        }
    }
    return path;
}



vector<int> BFS(int diamond_array[],bool diamond_extra_bytes_array[],int array_size,int starting_diamond_index)
{
    vector<int> path;
    queue<int> wait_list;
    unordered_set<int> lala;
    // wait_list.push(0);
    int q=0;

    int index = ith_diamond(diamond_extra_bytes_array,array_size,starting_diamond_index);
    wait_list.push(get_starting_index(diamond_extra_bytes_array,index));
    
    // wait_list.push(index_to_diamond_id.begin()->first);
    while(!wait_list.empty())
    {
        index = wait_list.front();
        wait_list.pop();
        int i=index+1;
        // int diamond_id = index_to_diamond(diamond_extra_bytes_array,array_size,index);
        // int diamond_id = index_to_diamond_id[index];
        int diamond_id = get_starting_index(diamond_extra_bytes_array,index);
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

unordered_set<int> vertex_degree_full_structure(vector<Diamond> &diamond_list,int id)
{
    unordered_set<int> diamond_ids;
    unordered_set<int> tetra_ids;
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
                for (Tetrahedron* tetra : diamond_list[i].get_tetra_list())
                {
                    tetra_ids.insert(tetra->get_id());
                }
                return tetra_ids;
                // return diamond_list[i].get_tetra_list().size();
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
        int warning;
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
                warning=0;
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
                tetra_ids.insert(current.to->get_tetra_list()[indexes[0]/2]->get_id());
                tetra_ids.insert(current.to->get_tetra_list()[indexes[1]/2]->get_id());
                tetra_ids.insert(current.to->get_tetra_list()[indexes[2]/2]->get_id());
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
                warning=1;
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
                tetra_ids.insert(current.to->get_tetra_list()[indexes[0]/2]->get_id());
                tetra_ids.insert(current.to->get_tetra_list()[indexes[1]/2]->get_id());
                tetra_ids.insert(current.to->get_tetra_list()[indexes[2]/2]->get_id());
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
                warning=2;
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
                    tetra_ids.insert(current.to->get_tetra_list()[i/2]->get_id());
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
            warning=3;
            total_degree+=1;
            tetra_ids.insert(current.to->get_tetra_list()[0]->get_id());
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
        // if (tetra_ids.size()!=total_degree)
        // {
        //     cout<<warning<<endl;
        // }
        
        // sleep(1);
    }
    return tetra_ids;
}

struct Next_
{
    int from_index;
    int to_index;
    int from_face_index;
    int vertex_index;
};


int vertex_degree_with_minimal_array(int (diamond_array)[],bool (diamond_extra_bytes_array)[],int diamond_array_size,
vector<tuple<int,int,int>> &permutation_array,vector<tuple<int,int,int>> &face_array,int id)
{
    unordered_set<int> diamond_ids;
    unordered_set<int> tetra_ids;
    stack<Next_> stack_face;
    int total_degree=0;
    cout<<id<<endl;
    int index = diamond_id_to_index(diamond_extra_bytes_array,diamond_array_size,id);
    cout<<"size "<<diamond_array_size<<endl;
    cout<<"index :"<<index<<endl;
    // display_face_diamond(diamond_extra_bytes_array,face_array,id);
    int size = diamond_size(diamond_extra_bytes_array,diamond_array_size,index);
    cout<<"size"<<endl;
    Next_ first;
    first.from_index=index;
    first.to_index=diamond_array[index];
    first.from_face_index=0;
    // cout<<"size : "<<size<<endl;
    // cout<<diamond_extra_bytes_array[index]<<endl;
    if (size==4)
    {
        // cout<<"size is 4"<<endl;
        cout<<"error0"<<endl;
        
        first.from_index=index+1;
        first.from_face_index=1;
        first.vertex_index=0;
        first.to_index=diamond_array[index+1];
        // display_face(face_array[index-3]);
        // display_face(face_array[index-2]);
        // display_face(face_array[index-1]);
        display_face(face_array[index+1]);
        display_face(face_array[index+2]);
        display_face(face_array[index+3]);
        display_face(face_array[diamond_array[index+3]]);
    }
    else
    {
        cout<<"error1"<<endl;
        first.vertex_index=2;
    }
    if (first.to_index==-1)
    {
        cout<<"error2"<<endl;
        if (size>4)
        {
            cout<<"error3"<<endl;
            // cout<<"shit1"<<endl;
            for(int j=0;j<size;j+=2)
            {
                if (diamond_array[index+j]!=-1)
                {
                    first.from_index=index+j;
                    first.to_index=diamond_array[index+j];
                    first.from_face_index=j;    
                    break;
                }
            }   
        }
        else
        {
            cout<<"error4"<<endl;
            // cout<<"shit2"<<endl;
            if (diamond_array[index+2]!=-1)
            {
                first.from_index=index+2;
                first.to_index=diamond_array[index+2];
                first.from_face_index=2;   
            }
            if (diamond_array[index+3]!=-1)
            {
                first.from_index=index+3;
                first.to_index=diamond_array[index+3];
                first.from_face_index=3; 
            }
        }                             
    }
    if (first.to_index==-1)
    {
        cout<<"error5"<<endl;
        // cout<<"shit3"<<endl;
        if (size==4)
        {
            return 1;
        }
        return size/2;
        // return total_degree;
        // return tetra_ids;
    }
    stack_face.push(first);

    while (!stack_face.empty())
    {
        cout<<"a"<<endl;
        int warning;
        Next_ current = stack_face.top();
        stack_face.pop();
        cout<<"b"<<endl;
        // cout<<"error_0"<<endl;
        get_starting_index(diamond_extra_bytes_array,current.to_index);
        cout<<"c"<<endl;
        // cout<<"error_00"<<endl;
        // cout<<"From index : "<<current.from_index<<endl;
        // cout<<"To index : "<<current.to_index<<endl;
        if (current.to_index>=0 && current.to_index<diamond_array_size && diamond_ids.count(get_starting_index(diamond_extra_bytes_array,current.to_index))==0)
        {
            diamond_ids.insert(get_starting_index(diamond_extra_bytes_array,current.to_index));
        }
        else
        {
            cout<<"else "<<current.to_index<<endl;
            cout<<stack_face.size()<<endl;
            cout<<"x"<<endl;
            continue;
        }
        // cout<<"error_01"<<endl;
        // cout<<"b"<<endl;
        // cout<<get_starting_index(diamond_extra_bytes_array,current.to_index)<<endl;        

        cout<<"ongoing face :" ;
        display_face(face_array[current.to_index]);
        // display_face(face_array[current.to_index]);
        // cout<<"error_0"<<endl;
        cout<<current.to_index<<" "<<diamond_array_size<<endl;
        int cc = index_to_diamond_id(diamond_extra_bytes_array,diamond_array_size,current.to_index);
        // cout<<"error_1"<<endl;
        // cout<<"cc "<<cc<<endl;
        // cout<<endl;
        // display_face_diamond(diamond_extra_bytes_array,face_array,cc);
        // cout<<endl;
        int neighbour_face_size = diamond_size(diamond_extra_bytes_array,diamond_array_size,current.to_index);
        // cout<<"size : "<<neighbour_face_size<<endl;
        int neighbour_face_index = -1;
        // cout<<"c"<<endl;
        int neighbour_starting_index = get_starting_index(diamond_extra_bytes_array,current.to_index);
        // cout<<"error_02"<<endl;
        if (neighbour_starting_index!=0)
        {
            neighbour_face_index=current.to_index % neighbour_starting_index;
        }
        else
        {
            neighbour_face_index=current.to_index;
        }

        // cout<<"error_1"<<endl;
        cout<<"starting index : "<<neighbour_starting_index<<endl;
        cout<<"neighbour face index :"<<neighbour_face_index<<endl;
        if (neighbour_face_index==-1)
        {
            cout<<"unknown face"<<endl;
            assert(true==false);
        }
        cout<<"current.vertex_index : "<<current.vertex_index<<endl;
        cout<<"permutation : "<<get<0>(permutation_array[current.from_index])<<" "<<get<1>(permutation_array[current.from_index])<<" "<<get<2>(permutation_array[current.from_index])<<endl;
    //    cout<<"d"<<endl;
        if (neighbour_face_size>4)
        {
            // cout<<"error_2"<<endl;
            // cout<<"x4"<<endl;
            if (get<0>(permutation_array[current.from_index])==current.vertex_index)
            {
                warning=0;
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

                cout<<0<<endl;
                // cout<<diamond_array[neighbour_starting_index+indexes[0]]<<endl;
                // cout<<diamond_array[neighbour_starting_index+indexes[1]]<<endl;
                // cout<<diamond_array[neighbour_starting_index+indexes[2]]<<endl;
                cout<<neighbour_starting_index+indexes[0]<<endl;
                cout<<neighbour_starting_index+indexes[1]<<endl;
                cout<<neighbour_starting_index+indexes[2]<<endl;
                display_face(face_array[neighbour_starting_index+indexes[0]]);
                display_face(face_array[neighbour_starting_index+indexes[1]]);
                display_face(face_array[neighbour_starting_index+indexes[2]]);
                // display_face(face_array[diamond_array[neighbour_starting_index+indexes[0]]]);
                // display_face(face_array[diamond_array[neighbour_starting_index+indexes[1]]]);
                // display_face(face_array[diamond_array[neighbour_starting_index+indexes[2]]]);
                


                // tetra_ids.insert(current.to->get_tetra_list()[indexes[0]/2]->get_id());
                // tetra_ids.insert(current.to->get_tetra_list()[indexes[1]/2]->get_id());
                // tetra_ids.insert(current.to->get_tetra_list()[indexes[2]/2]->get_id());
                if (diamond_array[neighbour_starting_index+indexes[0]]!=-1)
                {
                    Next_ next0;
                    next0.from_index=neighbour_starting_index+indexes[0];
                    next0.to_index=diamond_array[neighbour_starting_index+indexes[0]];
                    next0.from_face_index=indexes[0];
                    next0.vertex_index=0;
                    stack_face.push(next0);
                    
                }
                if (diamond_array[neighbour_starting_index+indexes[1]]!=-1)
                {
                    Next_ next1;
                    next1.from_index=neighbour_starting_index+indexes[1];
                    next1.to_index=diamond_array[neighbour_starting_index+indexes[1]];
                    next1.from_face_index=indexes[1];
                    next1.vertex_index=1;
                    stack_face.push(next1);
                    
                }
                if (diamond_array[neighbour_starting_index+indexes[2]]!=-1)
                {
                    Next_ next2;
                    next2.from_index=neighbour_starting_index+indexes[2];
                    next2.to_index=diamond_array[neighbour_starting_index+indexes[2]];
                    next2.from_face_index=indexes[2];
                    next2.vertex_index=1;
                    stack_face.push(next2);
                    
                }
                // cout<<"error_3"<<endl;
                continue;
            }
            if (get<1>(permutation_array[current.from_index])==current.vertex_index)
            {
                // cout<<"error_4"<<endl;
                warning=1;
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
                // tetra_ids.insert(current.to->get_tetra_list()[indexes[0]/2]->get_id());
                // tetra_ids.insert(current.to->get_tetra_list()[indexes[1]/2]->get_id());
                // tetra_ids.insert(current.to->get_tetra_list()[indexes[2]/2]->get_id());
                
                cout<<1<<endl;
                // cout<<diamond_array[neighbour_starting_index+indexes[0]]<<endl;
                // cout<<diamond_array[neighbour_starting_index+indexes[1]]<<endl;
                // cout<<diamond_array[neighbour_starting_index+indexes[2]]<<endl;
                display_face(face_array[neighbour_starting_index+indexes[0]]);
                display_face(face_array[neighbour_starting_index+indexes[1]]);
                display_face(face_array[neighbour_starting_index+indexes[2]]);
                // display_face(face_array[diamond_array[neighbour_starting_index+indexes[0]]]);
                // display_face(face_array[diamond_array[neighbour_starting_index+indexes[1]]]);
                // display_face(face_array[diamond_array[neighbour_starting_index+indexes[2]]]);
                
                if (diamond_array[neighbour_starting_index+indexes[0]]!=-1)
                {
                    Next_ next0;
                    next0.from_index=neighbour_starting_index+indexes[0];
                    next0.to_index=diamond_array[neighbour_starting_index+indexes[0]];
                    next0.from_face_index=indexes[0];
                    next0.vertex_index=1;
                    stack_face.push(next0);
                    
                }
                if (diamond_array[neighbour_starting_index+indexes[1]]!=-1)
                {
                    Next_ next1;
                    next1.from_index=neighbour_starting_index+indexes[1];
                    next1.to_index=diamond_array[neighbour_starting_index+indexes[1]];
                    next1.from_face_index=indexes[1];
                    next1.vertex_index=0;
                    stack_face.push(next1);
                    
                }
                if (diamond_array[neighbour_starting_index+indexes[2]]!=-1)
                {
                    Next_ next2;
                    next2.from_index=neighbour_starting_index+indexes[2];
                    next2.to_index=diamond_array[neighbour_starting_index+indexes[2]];
                    next2.from_face_index=indexes[2];
                    next2.vertex_index=0;
                    stack_face.push(next2);
                    
                }
                // cout<<"error_5"<<endl;
                continue;
            }
            if (get<2>(permutation_array[current.from_index])==current.vertex_index)
            {
                // cout<<"error_6"<<endl;
                warning=2;
                int start;
                if (neighbour_face_index%2==0)
                {
                    start=0;
                }
                else
                {
                    start=1;
                }
                cout<<2<<endl;
                
                for (int i=start;i<neighbour_face_size;i+=2)
                {
                    total_degree+=1;
                    // tetra_ids.insert(current.to->get_tetra_list()[i/2]->get_id());
                    if (diamond_array[neighbour_starting_index+i]!=-1)
                    {
                        display_face(face_array[neighbour_starting_index+i]);
                        Next_ next;
                        next.from_index=neighbour_starting_index+i;
                        next.to_index=diamond_array[neighbour_starting_index+i];
                        next.from_face_index=i;
                        next.vertex_index=2;
                        stack_face.push(next);
                        
                    }
                }
                // cout<<"error_7"<<endl;
                continue;
            }
        }
        else
        {
            // cout<<"error_8"<<endl;
            warning=3;
            total_degree+=1;
            // tetra_ids.insert(current.to->get_tetra_list()[0]->get_id());
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

            cout<<3<<endl;
            // cout<<diamond_array[neighbour_starting_index+indexes[0]]<<endl;
            // cout<<diamond_array[neighbour_starting_index+indexes[1]]<<endl;
            // cout<<diamond_array[neighbour_starting_index+indexes[2]]<<endl;
            // display_face(face_array[neighbour_starting_index+indexes[0]]);
            // display_face(face_array[neighbour_starting_index+indexes[1]]);
            // display_face(face_array[neighbour_starting_index+indexes[2]]);
            // display_face(face_array[diamond_array[neighbour_starting_index+indexes[0]]]);
            // display_face(face_array[diamond_array[neighbour_starting_index+indexes[1]]]);
            // display_face(face_array[diamond_array[neighbour_starting_index+indexes[2]]]);
            cout<<endl;
            for (int i=neighbour_starting_index;i<neighbour_starting_index+diamond_size(diamond_extra_bytes_array,diamond_array_size,neighbour_starting_index);i++)
            {
                display_face(face_array[i]);
            }
            cout<<endl;
            int which_case;
            if (get<0>(permutation_array[current.from_index])==current.vertex_index)
            {
                which_case = x[neighbour_face_index][0];
            }
            if (get<1>(permutation_array[current.from_index])==current.vertex_index)
            {
                which_case = x[neighbour_face_index][1];
            }
            if (get<2>(permutation_array[current.from_index])==current.vertex_index)
            {
                which_case = x[neighbour_face_index][2];
            }
            
            vector<int> permutation = {
                get<0>(permutation_array[current.from_index]),get<1>(permutation_array[current.from_index]),
                get<2>(permutation_array[current.from_index])
            };
            

            for (int i=0;i<3;i++)
            {
                if (permutation[i]!=current.vertex_index)
                {
                    Next_ next0;
                    next0.from_index=neighbour_starting_index+indexes[i];
                    next0.to_index=diamond_array[neighbour_starting_index+indexes[i]];
                    next0.from_face_index=indexes[i];

                    if (x[indexes[i]][0]==which_case)
                    {
                        next0.vertex_index=0;
                    }
                    if (x[indexes[i]][1]==which_case)
                    {
                        next0.vertex_index=1;
                    }   
                    if (x[indexes[i]][2]==which_case)
                    {
                        next0.vertex_index=2;
                    }

                    stack_face.push(next0);
                    // cout<<"vertice "<<current.to->vertex_order[indexes[i]]<<endl;
                    display_face(face_array[neighbour_starting_index+indexes[i]]);
                    // display_face(face_array[diamond_array[neighbour_starting_index+indexes[i]]]);
                }
            }
            // cout<<"error_9"<<endl;
        }       
        // sleep(1);
    }
    cout<<"degree : "<<total_degree<<endl;
    return total_degree;
}