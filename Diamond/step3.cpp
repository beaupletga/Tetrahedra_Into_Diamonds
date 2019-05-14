#include "step3.h"

void step_3(vector<Tetrahedron> &tetra_list,vector<Diamond> &diamond_list)
{
    // for each tetra, we assign the size of its diamond and its position in it
    int tetra_array[tetra_list.size()];

    int diamond1_size=count_if(diamond_list.begin(),diamond_list.end(),[](Diamond i){return i.get_tetra_list().size()==1;});
    int diamond3_size=count_if(diamond_list.begin(),diamond_list.end(),[](Diamond i){return i.get_tetra_list().size()==3;});
    int diamond4_size=count_if(diamond_list.begin(),diamond_list.end(),[](Diamond i){return i.get_tetra_list().size()==4;});
    int diamond5_size=count_if(diamond_list.begin(),diamond_list.end(),[](Diamond i){return i.get_tetra_list().size()==5;});
    int diamond6_size=count_if(diamond_list.begin(),diamond_list.end(),[](Diamond i){return i.get_tetra_list().size()==6;});
    int diamond7_size=count_if(diamond_list.begin(),diamond_list.end(),[](Diamond i){return i.get_tetra_list().size()==7;});
    int diamond8_size=count_if(diamond_list.begin(),diamond_list.end(),[](Diamond i){return i.get_tetra_list().size()==8;});
    int diamond9_size=count_if(diamond_list.begin(),diamond_list.end(),[](Diamond i){return i.get_tetra_list().size()==9;});

    int array_size=diamond1_size*4+diamond3_size*6+diamond4_size*8+diamond5_size*10+
    diamond6_size*12+diamond7_size*14+diamond8_size*16+diamond9_size*18;
    int diamond_array[array_size];

    
    map<int,int> diamond_id_to_index;
    int index=0;
    for(int i=0;i<diamond_list.size();i++)
    {
        diamond_id_to_index[diamond_list[i].get_id()]=index;
        index+=diamond_list[i].get_neighbours().size();
    }

    index=0;
    for(int i=0;i<diamond_list.size();i++)
    {
        for(Diamond* diamond : diamond_list[i].get_neighbours())
        {
            if (diamond==NULL)
            {
                diamond_array[index]=NULL;
            }
            else
            {
                diamond_array[index]=diamond_id_to_index[diamond->get_id()];
            }
            index++;
        }
    }

    for(int i=0;i<tetra_list.size();i+=2)
    {
        tetra_array[i]=diamond_id_to_index[tetra_list[i].get_diamond_ref()->get_id()]+tetra_list[i].get_position_in_diamond();;
    }


    cout<<"Size : "<<array_size+tetra_list.size()<<endl;
    float size = (float)(array_size+tetra_list.size())/(float)tetra_list.size();
    cout<<size<<endl;
    
}
