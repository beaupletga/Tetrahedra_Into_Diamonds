#include "../include/visualization.h"

int id_to_index2(vector<Diamond> &diamond_list,int id)
{
    for(int i=0;i<diamond_list.size();i++)
    {
        if (diamond_list[i].get_id()==id)
        {
            return i;
        }
    }
    cout<<"ID : "<<id<<endl;
    assert(true==false);
    return -1;
}

// write in a csv the position of the tetrahedra
void visualize(vector<Tetrahedron> &tetra_list)
{
    ofstream output;
    output.open ("../data/Visualisation/visualize.csv");
    for (Tetrahedron tetra : tetra_list)
    {
        tuple<double,double,double> tmp = tetra.get_barycenter();
        output<<get<0>(tmp)<<","<<get<1>(tmp)<<","<<get<2>(tmp)<<","<<tetra.get_in_diamond()<<","<<tetra.get_is_on_boundary()<<"\n";
    }
    output.close();
}

// take a vector of tetrahedron id as input
// write in an off file the face of the tetrahedra to visualize
void visualize_subset_tetra(vector<Vertex> &vertex_list,vector<Tetrahedron> &tetra_list,vector<int> &tetras_id)
{
    ofstream output;
    output.open ("../data/Visualisation/visualize_subset_tetra.off");
    output<<"OFF\n";
    output<<vertex_list.size()<<" "<<tetras_id.size()*4<<" "<<0<<"\n";
    for (Vertex vertex : vertex_list)
    {
        output<<vertex.get_coords()[0]<<" "<<vertex.get_coords()[1]<<" "<<vertex.get_coords()[2]<<"\n";
    }
    for (int id : tetras_id)
    {
        double R = rand()%255;
        double G = rand()%255;
        double B = rand()%255;
        Tetrahedron tetra = tetra_list[id];
        vector<Vertex*> ids=tetra.get_vertices();
        output<<"3 "<<ids[0]->get_id()<<" "<<ids[1]->get_id()<<" "<<ids[2]->get_id()<<" "<<R<<" "<<G<<" "<<B<<"\n";
        output<<"3 "<<ids[0]->get_id()<<" "<<ids[2]->get_id()<<" "<<ids[3]->get_id()<<" "<<R<<" "<<G<<" "<<B<<"\n";
        output<<"3 "<<ids[1]->get_id()<<" "<<ids[2]->get_id()<<" "<<ids[3]->get_id()<<" "<<R<<" "<<G<<" "<<B<<"\n";
        output<<"3 "<<ids[0]->get_id()<<" "<<ids[1]->get_id()<<" "<<ids[3]->get_id()<<" "<<R<<" "<<G<<" "<<B<<"\n";
    }
    output.close();
}

// take a vector of diamond id
// write in an off file the faces of diamonds to visualize
void visualize_subset_diamond(vector<Vertex> &vertex_list,vector<Diamond> &diamond_list,vector<int> &diamonds_id)
{
    ofstream output;
    output.open("../data/Visualisation/visualize_subset_diamond.off");
    output<<"OFF\n";

    int size=0;

    for (int id : diamonds_id)
    {
        int index=id_to_index2(diamond_list,id);
        size+=diamond_list[index].get_external_faces().size();
    }

    output<<vertex_list.size()<<" "<<size<<" "<<0<<"\n";
    for (Vertex vertex : vertex_list)
    {
        output<<vertex.get_coords()[0]<<" "<<vertex.get_coords()[1]<<" "<<vertex.get_coords()[2]<<"\n";
    }
    for (int id : diamonds_id)
    {
        int index=id_to_index2(diamond_list,id);
        double R = rand()%255;
        double G = rand()%255;
        double B = rand()%255;
        for(tuple<int,int,int> face : diamond_list[index].get_external_faces())
        {
            
            output<<"3 "<<get<0>(face)<<" "<<get<1>(face)<<" "<<get<2>(face)<<" "<<R<<" "<<G<<" "<<B<<"\n";
        }
    }
}

// write into an off file the central edges of diamonds 
void visualize_central_edges(vector<Vertex> &vertex_list,vector<Diamond> &diamond_list)
{
    ofstream output;
    output.open("../data/Visualisation/visualize_edges.off");
    output<<"OFF\n";
    int nb=0;
    for(Diamond diamond : diamond_list)
    {
        if (diamond.get_tetra_list().size()==1)
        {
            nb+=4;
        }
        else
        {
            nb+=2*diamond.get_tetra_list().size();
        }
    }
    // output<<vertex_list.size()<<" "<<edge_dict.size()*4<<" "<<0<<"\n";
    output<<vertex_list.size()<<" "<<nb<<" 1273"<<"\n";
    for (Vertex vertex : vertex_list)
    {
        output<<vertex.get_coords()[0]<<" "<<vertex.get_coords()[1]<<" "<<vertex.get_coords()[2]<<"\n";
    }
    for (Diamond diamond : diamond_list)
    {
        for(tuple<int,int,int> face : diamond.get_external_faces())
        {
            output<<"3 "<<get<0>(face)<<" "<<get<1>(face)<<" "<<get<2>(face)<<"\n";
        }
    }
    output.close();

    output.open("../data/Visualisation/visualize_edges.edges");
    for (Diamond diamond : diamond_list)
    {
        double R = rand()%255;;
        double G = rand()%255;;
        double B = rand()%255;;

        int vertex1 = diamond.get_central_edge().first;
        int vertex2 = diamond.get_central_edge().second;
        if (vertex1!=vertex2)
        {
            output<<vertex1<<" "<<vertex2<<" "<<R<<" "<<G<<" "<<B<<"\n";
        }        
    }
    output.close();
}

// take a vector of double as input
// write them into a csv file
void write_in_csv(vector<double> &list,string name)
{
    ofstream output;
    string filename = "/home/gabriel/Documents/Stage_X/Algorithms/Diamond/data/"+name;
    output.open(filename,std::ofstream::app);
    for (auto i : list)
    {
        output<<i<<',';
    }
    output<<"\n";
    output.close();
}
