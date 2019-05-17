#include "../include/step3.h"


// this step aims at choosing an anchor vertex for each diamond
// such that any vertex is linked to only one diamond
void step_3(vector<Diamond> &diamond_list,vector<Vertex> &vertex_list)
{
    map<int,vector<pair<int,int>>> tmp;
    for(Diamond diamond : diamond_list)
    {  
        int vertex1 =  diamond.get_central_edge().first;
        int vertex2 =  diamond.get_central_edge().second;
        tmp[vertex1].push_back(diamond.get_central_edge());
        tmp[vertex2].push_back(diamond.get_central_edge());
    }

    vector<pair<int,pair<int,int>>> lalaa;
    while(tmp.size()>0)
    {
        pair<int,vector<pair<int,int>>> it = *min_element(tmp.begin(),tmp.end(),[](pair<int,vector<pair<int,int>>> i,pair<int,vector<pair<int,int>>> j){return i.second.size()<j.second.size();});
        // cout<<it.first<<it.second.size()<<endl;
        pair<int,pair<int,int>> w = {it.first,{it.second[0]}};
        lalaa.push_back(w);

        tmp.erase(it.first);
        for(pair<int,vector<pair<int,int>>> j : tmp)
        {
            for(int k=0;k<j.second.size();k++)
            {
                if(j.second[k].first==it.second[0].first && j.second[k].second==it.second[0].second)
                {
                    tmp[j.first].erase(tmp[j.first].begin()+k);
                }
            }
            if(tmp[j.first].size()==0)
            {
                tmp.erase(j.first);
            }
        }
    }
    cout<<lalaa.size()/(double)vertex_list.size()<<endl;
}