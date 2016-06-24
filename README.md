# 3D-Placement

This is the team project for the OOP course. It tries to optimize the volume of the placement of a set of cubes.

## Interfaces

### Box

Defined with three edge lengths, `T`, `X` and `Y`. Note that a Box is independent of the order of these lengths, i.e, two Boxs are the same if and only if their corresponding edge lengths can be identical after being reordered arbitrarily.

* int T,X,Y	
* getVolume
* randomRotate  // Randomly swap T,X and Y.

### Point

Represented by its coordinates, i.e, the coordinates of the vector from the origin to it. The Point here lies in 3D space.

### PlacedBox: public Box

An OrientedBox with a specified position.

* point pt
* getDiagonalPointA
* getDiagonalPointB

### BoxPackage

A set of PlacedBoxs.

* std::vector&lt;PlacedBox&rt; Boxes  
* add: adding a placed cuboid
* getBoundingBox
* PackageisLegal // Detect if Boxes are collide with others
* GetVolumn // the sum of the volumn of Boxes.

### BoxPerturber  // Used in SA algorithm

Abstract

* virtual getBoxPackage = 0
* virtual perturb(double degree) = 0

### ContourStructure 

Abstract

* int Update(int x1, int y1, int x2, int y2, int add) // Search the max value and modify it. Used in T-tree.

### DoubleLink :: ContourStructure

### SegmentTree :: ContourStructure

### TTree: BoxPerturber

T-tree representation for a *compact* BoxPackage.

### BoxPerturberFactory

Abstract

* getBoxPerturber

### TTreeFactory : BoxPerturbStrategy

### BoxPackageValueStrategy // Used in SA algorithm

Abstract.

* getWeight(const BoxPackage&)

### BoxVolume: BoxPackageValueStrategy 

### SAOptimalConfig // Fundamental parameters used in SA algorithm 

### BoxPacker // the User Interface Class

Abstract.

* virtual packBoxes(const vector&lt;Box&rt;&) = 0

### SAOptimalBoxPacker: BoxPacker

Simulated Annealing algorithm.

* BoxPerturberFactory
* BoxPackageValueStrategy
* SAOptimalConfig
* SAOptimalBoxPacker(BoxPerturberFactory, BoxPackageValueStrategy, SAOptimalConfig) // Construction Function.

## Reference

Yuh, Yang & Chang, 2009. T-Trees: A Tree-Based Representation for Temporal and Three-Dimensional Floorplanning. *ACM Transactions on Design Automation of Electronic Systems, Vol.14*

