#include "../include/benchmark.h"

// Ths file aims at benchmarking in term of time and number of isolated tetra

void time_to_access_ith_diamond(bool diamond_extra_bytes_array[],int array_size,int diamond_number)
{
    double count_time=0;
    for (int i=0;i<diamond_number;i++)
    {
        auto start = chrono::high_resolution_clock::now(); 
        ith_diamond(diamond_extra_bytes_array,array_size,i);
        auto stop = chrono::high_resolution_clock::now(); 
        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start); 
        count_time+=duration.count();
    }
    cout<<"Average time to access ith diamond : "<<count_time*1e-6/diamond_number<<" s"<<endl;
}

void time_to_access_ith_tetra(bool diamond_extra_bytes_array[],int array_size,int tetra_number)
{
    double count_time=0;
    for (int i=0;i<tetra_number-1;i++)
    {
        auto start = chrono::high_resolution_clock::now(); 
        ith_tetra(diamond_extra_bytes_array,array_size,i);
        auto stop = chrono::high_resolution_clock::now(); 
        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start); 
        count_time+=duration.count();
    }
    cout<<"Average time to access ith tetra : "<<count_time*1e-6/(tetra_number-1)<<" s"<<endl;
}

void time_to_compute_vertex_degree(int diamond_array[],bool diamond_extra_bytes_array[],int array_size,vector<tuple<int,int,int>> &permutation_array,
vector<tuple<int,int,int>> &face_array,int vertex_number)
{
    streambuf *old = cout.rdbuf(0);
    double count_time=0;
    for (int i=0;i<vertex_number;i++)
    {
        auto start = chrono::high_resolution_clock::now(); 
        vertex_degree_with_minimal_array(diamond_array,diamond_extra_bytes_array,array_size,permutation_array,face_array,i);
        auto stop = chrono::high_resolution_clock::now(); 
        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start); 
        count_time+=duration.count();
    }
    cout.rdbuf(old);
    cout<<"Average time to compute the vertex degree : "<<count_time*1e-6/vertex_number<<" s"<<endl;
}

void time_to_compute_BFS(int diamond_array[],bool diamond_extra_bytes_array[],int array_size,vector<tuple<int,int,int>> &permutation_array,
vector<tuple<int,int,int>> &face_array,int diamond_number)
{
    double count_time=0;
    for (int i=0;i<diamond_number;i++)
    {
        auto start = chrono::high_resolution_clock::now(); 
        BFS(diamond_array,diamond_extra_bytes_array,array_size,i);
        auto stop = chrono::high_resolution_clock::now(); 
        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start); 
        count_time+=duration.count();
    }
    cout<<"Average time to compute BFS : "<<count_time*1e-6/diamond_number<<" s"<<endl;
}