#include "visualization.h"

void visualize(vector<Tetrahedron> &tetra_list)
{
    ofstream output;
    output.open ("visualize.csv");
    for (Tetrahedron tetra : tetra_list)
    {
        tuple<double,double,double> tmp = tetra.get_barycenter();
        output<<get<0>(tmp)<<","<<get<1>(tmp)<<","<<get<2>(tmp)<<","<<tetra.get_in_diamond()<<","<<tetra.get_is_on_boundary()<<"\n";
    }
    output.close();
}


void visualize_diamond_isolated(vector<Vertex> &vertex_list,vector<Tetrahedron> &tetra_list, map<tuple<int,int>,vector<Tetrahedron*>>& edge_dict, map<tuple<int,int>,vector<Vertex*>>& edge_to_vertex)
{
    int nb_isolated = 4*count_if(tetra_list.begin(),tetra_list.end(),[](Tetrahedron i){return !i.get_in_diamond() && i.get_is_on_boundary();});
    // int nb_isolated = 4*
    ofstream output;
    output.open("visualize.off");
    output<<"OFF\n";
    output<<vertex_list.size()<<" "<<nb_isolated<<" "<<0<<"\n";
    for (Vertex vertex : vertex_list)
    {
        output<<vertex.get_coords()[0]<<" "<<vertex.get_coords()[1]<<" "<<vertex.get_coords()[2]<<"\n";
    }
    for (Tetrahedron tetra : tetra_list)
    {
        if (!tetra.get_in_diamond() && tetra.get_is_on_boundary())
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
    //     if (i==400)
    //     {
    //         break;
    //     }
    //     i++;

    //     double R;
    //     double G;
    //     double B;
    //     if (edge_dict[edge.first].size()==3)
    //     {
    //         R=255;
    //         G=0;
    //         B=0;
    //     }
    //     else if (edge_dict[edge.first].size()==4)
    //     {
    //         R=255;
    //         G=102;
    //         B=0;
    //     }
    //     else if (edge_dict[edge.first].size()==5)
    //     {
    //         R=255;
    //         G=204;
    //         B=102;
    //     }
    //     else if (edge_dict[edge.first].size()==6)
    //     {
    //         R=204;
    //         G=255;
    //         B=102;
    //     }
    //     else if (edge_dict[edge.first].size()==7)
    //     {
    //         R=102;
    //         G=255;
    //         B=51;
    //     }
    //     else
    //     {
    //         R=0;
    //         G=153;
    //         B=51;
    //     }


    //     // double R = rand()%256;
    //     // double G = rand()%256;
    //     // double B = rand()%256;
    //     // double R=RR;
    //     // double G=GG;
    //     // double B=BB;
    //     for(Tetrahedron* tetra : edge_dict[edge.first])
    //     {
    //         // R = R+20;
    //         // G = G+20;
    //         // B = B+20;
    //         vector<Vertex*> ids=tetra->get_vertices();
    //         output<<"3 "<<ids[0]->get_id()<<" "<<ids[1]->get_id()<<" "<<ids[2]->get_id()<<" "<<R<<" "<<G<<" "<<B<<"\n";
    //         output<<"3 "<<ids[0]->get_id()<<" "<<ids[2]->get_id()<<" "<<ids[3]->get_id()<<" "<<R<<" "<<G<<" "<<B<<"\n";
    //         output<<"3 "<<ids[1]->get_id()<<" "<<ids[2]->get_id()<<" "<<ids[3]->get_id()<<" "<<R<<" "<<G<<" "<<B<<"\n";
    //         output<<"3 "<<ids[0]->get_id()<<" "<<ids[1]->get_id()<<" "<<ids[3]->get_id()<<" "<<R<<" "<<G<<" "<<B<<"\n";
    //     }
    // }

    output.close();
}
