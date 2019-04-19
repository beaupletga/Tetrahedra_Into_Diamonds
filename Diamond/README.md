# 3D-Mesh-Compression

Most of the time, when we are dealing with meshes, we are are dealing with surfasic ones (a triangulation of points). However in many applications we need a mesh of the boundary AND the volume. The latter are called volume mesh and consist in a tetrahedrisation of the space. A tetrahedron is a 3-simplex with 4 faces, 6 edges and 4 vertices.

A tetrahedrisation can be encoded by enumerating the position of each vertex (the geometry) and then enumerating all the tetrahedra according using the indices of their vertices. This is the model choosen for most representation of meshes (.OBJ,.OFF...). However the access to any part of the mesh are costly (in complexity) and we can't make any traversal of the mesh.

The idea of this repo is to take as input such files and encoding a compressed representation of the mesh. However, our solution must be allowing fast access to any part of the mesh (vertices, faces or tetrahedron) and quick traversal of the mesh (going from one tetrahedron to one of its neighbour...).

### Diamond
#### Description
The algorithm try to reduce the number of necessary references for a lossless storage of a 3D mesh.
We use a diamond pattern for aggregating tetrahedra between eachother and as consequences avoiding storing internal references.

#### TODO

- Diamond Class (define the internal order in the diamond, define the references towards the neighboring diamonds, include the vertices into the diamond class)

- Step 1 : Using heuristics for a better matching vertex-edge such that the number of conflicts (tetrahedron with at least 2 edges choosen) and empty tetrahedron is as small as possible. Several choices : Using some kind of graph process (starting from one tetrahedra then going to the neighboring one... until all tetrahedra have been seen), starting from edges with high tetra degree, normal matching then "refine" by matching adjacents unmatched tetra
All these heuristics need to be benchmarked for a rational comparison.

- Step 2 : Start it : Creating Diamond for each edge matched with some tetra. Create diamond for unmatched tetra (this is costly)

- Visualize if the mathing is correct (using an external tool or to develop one)