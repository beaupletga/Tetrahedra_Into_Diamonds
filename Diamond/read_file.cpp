#include "read_file.h"

vector<double> split(string line,int start_index,int end_index)
{
    vector<double> list;
    string tmp="";
    for(int i=0;i<line.size();i++)
    {
        if (line[i]==' ')
        {
            double word = atof(tmp.c_str());
            list.push_back(word);
            tmp="";
        }
        else
        {
            tmp=tmp+line[i];
        }
    }
    if (line.back()!=' ')
    {
        list.push_back(atof(tmp.c_str()));
    }
    vector<double>::const_iterator first = list.begin() + start_index;
    vector<double>::const_iterator last = list.begin() + end_index;
    vector<double> newVec(first, last);
    return newVec;
}

tuple<vector<vector<double>>,vector<vector<double>>> read_tet_file(string filename)
{
    string line;
    int n_v,n_t;
    int count=0;
    vector<vector<double>> whole_list;
    ifstream myfile(filename);
    getline (myfile,line);
    n_v=split(line,0,1)[0];
    getline (myfile,line);
    n_t=split(line,0,1)[0];

    if (myfile.is_open())
    {
        while (getline (myfile,line))
        {
            if (count<n_v)
            {
                whole_list.push_back(split(line,0,3));
            }
            else
            {
                whole_list.push_back(split(line,1,5));
            }
            count+=1;
        }
        myfile.close();
    }
    else 
    {
        cout << "Unable to open file"; 
    }

    vector<vector<double>>::const_iterator first = whole_list.begin();
    vector<vector<double>>::const_iterator last = whole_list.begin() + n_v;
    vector<vector<double>> geometry_list(first, last);
    first = whole_list.begin()+ n_v;
    last = whole_list.end();
    vector<vector<double>>conectivity_list(first, last);
    tuple<vector<vector<double>>,vector<vector<double>>> lala = make_tuple(geometry_list,conectivity_list); 
    return lala;
}

tuple<vector<vector<double>>,vector<vector<double>>> read_mesh_file(string filename)
{
    string line;
    int n_v,n_t,n_tetra;
    int count=0;
    vector<vector<double>> whole_list;
    ifstream myfile(filename);
    getline (myfile,line);
    getline (myfile,line);
    getline (myfile,line);
    getline (myfile,line);
    n_v= stoi(line);
    if (myfile.is_open())
    {
        // vertices
        for(int i=0;i<n_v;i++)
        {
            getline (myfile,line);
            whole_list.push_back(split(line,0,3));
        }

        // faces
        getline (myfile,line);
        getline (myfile,line);
        n_t= stoi(line);

        for(int i=0;i<n_t;i++)
        {
            getline (myfile,line);
        }

        // tetra
        getline (myfile,line);
        getline (myfile,line);
        n_tetra= stoi(line);

        for(int i=0;i<n_tetra;i++)
        {
            getline (myfile,line);
            whole_list.push_back(split(line,0,4));
        }
        cout<<"Number vertices : "<<n_v<<endl;
        cout<<"Number tetra : "<<n_tetra<<endl;
        myfile.close();
    }
    else 
    {
        cout << "Unable to open file"; 
    }
    
    vector<vector<double>>::const_iterator first = whole_list.begin();
    vector<vector<double>>::const_iterator last = whole_list.begin() + n_v;
    vector<vector<double>> geometry_list(first, last);
    first = whole_list.begin()+ n_v;
    last = whole_list.end();
    vector<vector<double>>conectivity_list(first, last);

    // because in mesh file, indexes start at 1 instead of 0
    for (vector<double> &i : conectivity_list)
    {
        for (double &j : i )
        {
            j--;
        }
    }

    tuple<vector<vector<double>>,vector<vector<double>>> lala = make_tuple(geometry_list,conectivity_list); 
    return lala;
}




// int main()
// {
//     tuple<vector<vector<double>>,vector<vector<double>>> result;
//     result=read_mesh_file("ball.mesh");
//     // result=read_file("cow.tet");
//     // for (vector<double> i : get<1>(result))
//     // {
//     //     cout<<i[0]<<" "<<i[1]<<" "<<i[2]<<" "<<i[3]<<" "<<endl;
//     // }
//     return 0;
// }

