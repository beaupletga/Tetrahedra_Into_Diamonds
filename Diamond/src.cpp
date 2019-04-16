#include "src.h"

// read a set of vertices and return all possible edges
vector<tuple<int,int>> enumerate_edges(vector<Vertex> vertices)
{
    vector<tuple<int,int>> edges;
    for(int i=0;i<vertices.size()-1;i++)
    {
        for (int j=i+1;j<vertices.size();j++)
        {
            tuple<int,int> tmp=make_tuple(vertices[i].get_id(),vertices[j].get_id());
            edges.push_back(tmp);
        }
    }
    return edges;
}

// make a dict of <id of vertex,pointers towards tetra containing this vertex>
std::map<int,vector<Tetrahedron *>> make_vertex_dict(vector<Tetrahedron> tetra_list)
{
    std::map<int,vector<Tetrahedron *>> vertex_dict;
    // iterate over the triangles and add the 3 edges into edge_dict
    for(int i=0;i<tetra_list.size();i++)
    {
        for (Vertex j : tetra_list[i].get_vertices())
        {
            if(vertex_dict.count(j.get_id())==0)
            {
                vector<Tetrahedron *> tmp={&tetra_list[i]};
                vertex_dict.insert(std::pair<int,vector<Tetrahedron *>>(j.get_id(),tmp));
            }
            else
            {
                vertex_dict.find(j.get_id())->second.push_back(&tetra_list[i]);
            }
        }
    }
    return vertex_dict;
}

// make a dict of <edge,pointers towards tetra containing this edge>
// where edge is a tuple <id of vertex,id of vertex> which are both int
std::map<tuple<int,int>,vector<Tetrahedron *>> make_edge_dict(vector<Tetrahedron> tetra_list)
{
    // each edge is a tuple of vertice and belong to at least 1 tetra
    std::map<tuple<int,int>,vector<Tetrahedron *>> edge_dict;
    // iterate over the triangles and add the 3 edges into edge_dict
    for(int i=0;i<tetra_list.size();i++)
    {
        for (tuple<int,int> j : enumerate_edges(tetra_list[i].get_vertices()))
        {
            if(edge_dict.count(j)==0)
            {
                vector<Tetrahedron *> tmp={&tetra_list[i]};
                edge_dict.insert(pair<tuple<int,int>,vector<Tetrahedron *>>(j,tmp));
            }
            else
            {
                edge_dict.find(j)->second.push_back(&tetra_list[i]);
            }
        }
    }
    return edge_dict;
}

// add references to the neighboring edges
// index : to which vertex do we have to add neighbours
// vertex_list : vertex list in a tetrahedra
void add_neighours(int index,vector<Vertex *> vertex_list)
{
    vector<Vertex *> neighbours;
    for(int i=0;i<vertex_list.size();i++)
    {
        if (i!=index)
        {
            neighbours.push_back(vertex_list[i]);
            vertex_list[index]->add_neighbours(neighbours);
        }
    }
}


// vertex_list and tetra_list are empty
// read result which is a tuple containing both the geometry and connectivity
// encapsulate both into proper classes
void preprocessing_tetra(tuple<vector<vector<double>>,vector<vector<double>>> result, vector<Vertex>& vertex_list, vector<Tetrahedron>& tetra_list)
{
    vector<vector<double>> geometry = get<0>(result);
    vector<vector<double>> connectivity = get<1>(result);

    for(int i=0;i<geometry.size();i++)
    {
        Vertex tmp=Vertex(i,geometry[i]);
        vertex_list.push_back(tmp);
    }

    for(int i=0;i<connectivity.size();i++)
    {
        vector<Vertex *> tmp0 ={&vertex_list[connectivity[i][0]],&vertex_list[connectivity[i][1]],&vertex_list[connectivity[i][2]],&vertex_list[connectivity[i][3]]};
        Tetrahedron tmp1=Tetrahedron(i,tmp0);
        tetra_list.push_back(tmp1);
        add_neighours(0,tmp0);
        add_neighours(1,tmp0);
        add_neighours(2,tmp0);
        add_neighours(3,tmp0);
    }
}   

// in average, how many tetra are adjacents to a vertex
double average_vertex_degree(std::map<int,vector<Tetrahedron *>> vertex_dict)
{
    double count=0;

    for (std::pair<int, vector<Tetrahedron *>> element : vertex_dict) 
    {		
        count+=element.second.size();
	}
    return count/vertex_dict.size();
}

// in average, how many tetra are adjacents to a vertex
double average_edge_degree(std::map<tuple<int,int>,vector<Tetrahedron *>> edge_dict)
{
    double count=0;

    for (std::pair<tuple<int,int>, vector<Tetrahedron *>> element : edge_dict) 
    {		
        count+=element.second.size();
	}
    return count/edge_dict.size();
}

// how many edges per vertex
double average_edges_per_vertex(vector<Vertex> vertex_list)
{
    double count=0;

    for (Vertex element : vertex_list) 
    {		
        count+=element.get_neighbours().size();
	}
    return count/vertex_list.size();
}

Vertex * pick_random_edge(Vertex * vertex)
{
    int vertex_index =rand() % vertex->get_neighbours().size();
    return vertex->get_neighbours()[vertex_index];
}

void step_1(vector<Vertex> vertex_list)
{
    map<tuple<int,int>,vector<Vertex *>> edge_dict;
    for(int i=0;i<vertex_list.size();i++)
    {
        Vertex *v2 =pick_random_edge(&vertex_list[i]);
        tuple<int,int> tmp;
        if (vertex_list[i].get_id()<v2->get_id())
        {
            tmp= make_tuple(vertex_list[i].get_id(),v2->get_id());
        }
        else
        {
            tmp= make_tuple(v2->get_id(),vertex_list[i].get_id());
        }
        if (edge_dict.count(tmp)==0)
        {
            vector<Vertex *> vec_tmp={&vertex_list[i]};
            edge_dict.insert(pair<tuple<int,int>,vector<Vertex *>>(tmp,vec_tmp));
        }
        else
        {
            edge_dict.find(tmp)->second.push_back(&vertex_list[i]);
        }
    }
    int count=0;
    for (pair<tuple<int,int>,vector<Vertex *>> i : edge_dict)
    {
        if(i.second.size()>1)
        {
            count++;
        }
    }
    cout<<count<<endl;
}




    
// map<tuple<int,int>,vector<Tetrahedron>>::iterator it;
//     for ( it = edge_dict.begin(); it != edge_dict.end(); it++ )
//     {
//         for (int i=0;i<it->second.size()-1;i++)
//         {
//             for (int j=i+1;j<it->second.size();j++)
//             {
//                 it->second[i].get_neighbours().push_back(it->second[j]);
//                 it->second[j].get_neighbours().push_back(it->second[i]);
//             }
//         }
//     }


    





