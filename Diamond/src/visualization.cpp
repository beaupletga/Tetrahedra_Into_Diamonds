#include "../include/visualization.h"

void visualize(vector<Tetrahedron> &tetra_list)
{
    ofstream output;
    output.open ("../data/visualize.csv");
    for (Tetrahedron tetra : tetra_list)
    {
        tuple<double,double,double> tmp = tetra.get_barycenter();
        output<<get<0>(tmp)<<","<<get<1>(tmp)<<","<<get<2>(tmp)<<","<<tetra.get_in_diamond()<<","<<tetra.get_is_on_boundary()<<"\n";
    }
    output.close();
}


void visualize_all(vector<Vertex> &vertex_list,vector<Tetrahedron> &tetra_list)
{
    ofstream output;
    output.open("../data/visualize_all.off");
    output<<"OFF\n";
    output<<vertex_list.size()<<" "<<tetra_list.size()*4<<" "<<0<<"\n";
    for (Vertex vertex : vertex_list)
    {
        output<<vertex.get_coords()[0]<<" "<<vertex.get_coords()[1]<<" "<<vertex.get_coords()[2]<<"\n";
    }
    for (Tetrahedron tetra : tetra_list)
    {
        vector<Vertex*> ids=tetra.get_vertices();
        output<<"3 "<<ids[0]->get_id()<<" "<<ids[1]->get_id()<<" "<<ids[2]->get_id()<<"\n";
        output<<"3 "<<ids[0]->get_id()<<" "<<ids[2]->get_id()<<" "<<ids[3]->get_id()<<"\n";
        output<<"3 "<<ids[1]->get_id()<<" "<<ids[2]->get_id()<<" "<<ids[3]->get_id()<<"\n";
        output<<"3 "<<ids[0]->get_id()<<" "<<ids[1]->get_id()<<" "<<ids[3]->get_id()<<"\n";
    }
}

void visualize_diamond_isolated(vector<Vertex> &vertex_list,vector<Tetrahedron> &tetra_list, map<tuple<int,int>,vector<Tetrahedron*>>& edge_dict, map<tuple<int,int>,vector<Vertex*>>& edge_to_vertex)
{
    int nb_isolated = 4*count_if(tetra_list.begin(),tetra_list.end(),[](Tetrahedron i){return !i.get_in_diamond();});
    // int nb_isolated = 4*
    ofstream output;
    output.open("../data/visualize.off");
    output<<"OFF\n";
    // output<<vertex_list.size()<<" "<<edge_dict.size()*4<<" "<<0<<"\n";
    output<<vertex_list.size()<<" "<<nb_isolated<<" "<<0<<"\n";
    for (Vertex vertex : vertex_list)
    {
        output<<vertex.get_coords()[0]<<" "<<vertex.get_coords()[1]<<" "<<vertex.get_coords()[2]<<"\n";
    }
    for (Tetrahedron tetra : tetra_list)
    {
        if (!tetra.get_in_diamond()) //&& tetra.get_is_on_boundary())
        {
            double R = rand()%255;
            double G = rand()%255;
            double B = rand()%255;

            vector<Vertex*> ids=tetra.get_vertices();
            output<<"3 "<<ids[0]->get_id()<<" "<<ids[1]->get_id()<<" "<<ids[2]->get_id()<<" "<<R<<" "<<G<<" "<<B<<"\n";
            output<<"3 "<<ids[0]->get_id()<<" "<<ids[2]->get_id()<<" "<<ids[3]->get_id()<<" "<<R<<" "<<G<<" "<<B<<"\n";
            output<<"3 "<<ids[1]->get_id()<<" "<<ids[2]->get_id()<<" "<<ids[3]->get_id()<<" "<<R<<" "<<G<<" "<<B<<"\n";
            output<<"3 "<<ids[0]->get_id()<<" "<<ids[1]->get_id()<<" "<<ids[3]->get_id()<<" "<<R<<" "<<G<<" "<<B<<"\n";
        }
    }
    // int i=0;
    // for (pair<tuple<int,int>,vector<Vertex*>> edge : edge_to_vertex)
    // {
    //     // if (i==2500)
    //     // {
    //     //     break;
    //     // }
    //     i++;
    //     double R = rand()%256;
    //     double G = rand()%256;
    //     double B = rand()%256;
    //     // cout<< edge_dict[edge.first].size()<<endl;
    //     // break;
    //     for(Tetrahedron* tetra : edge_dict[edge.first])
    //     {
    //         vector<Vertex*> ids=tetra->get_vertices();
    //         output<<"3 "<<ids[0]->get_id()<<" "<<ids[1]->get_id()<<" "<<ids[2]->get_id()<<" "<<R<<" "<<G<<" "<<B<<"\n";
    //         output<<"3 "<<ids[0]->get_id()<<" "<<ids[2]->get_id()<<" "<<ids[3]->get_id()<<" "<<R<<" "<<G<<" "<<B<<"\n";
    //         output<<"3 "<<ids[1]->get_id()<<" "<<ids[2]->get_id()<<" "<<ids[3]->get_id()<<" "<<R<<" "<<G<<" "<<B<<"\n";
    //         output<<"3 "<<ids[0]->get_id()<<" "<<ids[1]->get_id()<<" "<<ids[3]->get_id()<<" "<<R<<" "<<G<<" "<<B<<"\n";
    //     }
    //     // break;
    // }

    output.close();
}

int id_to_index(vector<Diamond> &diamond_list,int id)
{
    for(int i=0;i<diamond_list.size();i++)
    {
        if (diamond_list[i].get_id()==id)
        {
            return i;
        }
    }
    cout<<id<<endl;
    assert(true==false);
    return -1;
}

void visualize_diamond(vector<Vertex> &vertex_list,vector<Tetrahedron> &tetra_list,
vector<Diamond> &diamond_list,vector<int> &diamond_ids)
{
    int nb=0;
    for(int id : diamond_ids)
    {
        int index=id_to_index(diamond_list,id);
        if (diamond_list[index].get_tetra_list().size()==1)
        {
            nb+=4;
        }
        else
        {
            nb+=2*diamond_list[index].get_tetra_list().size();
        }
        
    }
    ofstream output;
    output.open("../data/visualize_path.off");
    output<<"OFF\n";
    // output<<vertex_list.size()<<" "<<edge_dict.size()*4<<" "<<0<<"\n";
    output<<vertex_list.size()<<" "<<nb<<" "<<0<<"\n";
    for (Vertex vertex : vertex_list)
    {
        output<<vertex.get_coords()[0]<<" "<<vertex.get_coords()[1]<<" "<<vertex.get_coords()[2]<<"\n";
    }
    for (int id : diamond_ids)
    {
        double R = rand()%255;
        double G = rand()%255;
        double B = rand()%255;
        int index=id_to_index(diamond_list,id);
        for(tuple<int,int,int> face : diamond_list[index].get_external_faces())
        {
            output<<"3 "<<get<0>(face)<<" "<<get<1>(face)<<" "<<get<2>(face)<<" "<<R<<" "<<G<<" "<<B<<"\n";
        }
    }
    output.close();
}

void visualize_central_edges(vector<Vertex> &vertex_list,vector<Diamond> &diamond_list)
{
    ofstream output;
    output.open("../data/visualize_edges.off");
    output<<"OFF\n";
    // output<<vertex_list.size()<<" "<<edge_dict.size()*4<<" "<<0<<"\n";
    output<<vertex_list.size()<<" "<<0<<" "<<diamond_list.size()<<"\n";
    for (Vertex vertex : vertex_list)
    {
        output<<vertex.get_coords()[0]<<" "<<vertex.get_coords()[1]<<" "<<vertex.get_coords()[2]<<"\n";
    }
    for (Diamond diamond : diamond_list)
    {
        double R = 155;
        double G = 155;
        double B = 155;
        
        int vertex1 = diamond.get_central_edge().first;
        int vertex2 = diamond.get_central_edge().second;

        output<<vertex1<<"->"<<vertex2<<";\n";//<" "<<R<<" "<<G<<" "<<B<<"\n";
    }
    output.close();
}
