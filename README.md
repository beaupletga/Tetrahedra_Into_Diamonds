# Tetrahedra Into Diamonds

This repo is the recap of my internship at LIX (Ecole Polytechnique), supervised by Luca Castelli Aleardi (http://www.lix.polytechnique.fr/~amturing/).

We present in this repo a new compact data structure for tetrahedral meshes (volumic meshes). Our data structure is named **Tetrahedra Into Diamonds** and uses on average 2.4rpt (references per tetrahedron), allows the navigation into the mesh in constant time and the computation of the hypersphere of a vertex in O(d).

### Overview of the Data Structure
Our algorithm groups tetrahera sharing a same edge and forming a cycle. We call this entity a "diamond". We use a BFS algorithm to create these diamonds. All the tetrahedra which are not into diamonds are called "isolated tetrahedra".<br />
We also re-order the diamond and the isolated tetrahedra such that the ith vertex is adjacent to the ith diamond/isolated tetra.<br/>
Finally, instead of using OFF file to describe a mesh, we have created a new format for exporting our data structure. This new format is 40% lighter than the original OFF file.

<img src="/Tetraedres_en_diamants/Rapport_et_Presentation/Images/full_diamond.png" width="250" height="250">*Figure showing 5 tetrahedra forming a diamond*
<img src="/Tetraedres_en_diamants/Rapport_et_Presentation/Images/diamond.png" width="250" height="250">*Figure showing diamonds*
<img src="/Tetraedres_en_diamants/Rapport_et_Presentation/Images/isolated_tetra.png" width="250" height="250">*Figure showing isolated tetrahedra*

All the code in this repo is native C++ code. No external library is used. Our data structure is essentially an array of integer. This way, our data structure can be transcripted easily in any other language.

Here are the steps for constructing our data structure : 

#### Step 1 : Grouping the tetrahedra into diamonds 

#### Step 2 : Creating diamonds

#### Step 3 : Anchor the vertices to the diamonds/isolated tetrahedron and computing permutations

#### Step 4 : Creating our data structure (an array of integer)


### Results

<img src="/Tetraedres_en_diamants/Rapport_et_Presentation/Images/boundary_RPT.png" width="250" height="250">*Evolution of the RPT according to the share of tetrahedra on the boundary of the mesh*

