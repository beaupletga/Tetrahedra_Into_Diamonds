#include "read_file.h"

vector<double> split(string line,int nb_elem=-1,bool is_conectivity=false)
{
    vector<double> list;
    string tmp="";
    int count=0;
    for(int i=0;i<line.size();i++)
    {
        if (line[i]==' ')
        {
            if (!(is_conectivity && count==0))
            {
                double word = atof(tmp.c_str());
                list.push_back(word);
                if (nb_elem==list.size())
                {
                    return list;
                }
            }
            tmp="";
            count+=1;
        }
        else
        {
            tmp=tmp+line[i];
        }
    }
    return list;
}

tuple<vector<vector<double>>,vector<vector<double>>> read_file(string filename)
{
    string line;
    int n_v,n_t;
    int count=0;
    vector<vector<double>> whole_list;
    ifstream myfile(filename);
    getline (myfile,line);
    n_v=split(line,1)[0];
    getline (myfile,line);
    n_t=split(line,1)[0];
    
    cout<<"Number vertices : "<<n_v<<endl;
    cout<<"Number tetra : "<<n_t<<endl;

    if (myfile.is_open())
    {
        while (getline (myfile,line))
        {
            if (count>=n_v)
            {
                whole_list.push_back(split(line,-1,true));
            }
            else
            {
                whole_list.push_back(split(line,-1,false));
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

// int main()
// {
//     tuple<vector<vector<double>>,vector<vector<double>>> result;
//     result=read_file("hand.tet");
//     cout<<get<1>(result)[0].size()<<endl;
//     return 0;
// }

