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

### BoxPacker // the User Interface Class

Abstract.

* virtual packBoxes(const vector&lt;Box&rt;&) = 0

### BoxPerturbStrategy  // Used in SA algorithm

Abstract

* fill
* clear
* virtual getBoxPackage = 0
* virtual perturb(double degree) = 0

### TTree: BoxPerturbStrategy

T-tree representation for a *compact* BoxPackage.

### BoxPackageValueStrategy // Used in SA algorithm

Abstract.

* getWeight(const BoxPackage&)

### BoxVolume: BoxPackageValueStrategy 

### SAOptimalConfig // Fundamental parameters used in SA algorithm 

### SAOptimalBoxPacker: BoxPacker

Simulated Annealing algorithm.

* OptimalBoxPacker(BoxPerturbStrategy, BoxPackageValueStrategy)

## Reference

Yuh, Yang & Chang, 2009. T-Trees: A Tree-Based Representation for Temporal and Three-Dimensional Floorplanning. *ACM Transactions on Design Automation of Electronic Systems, Vol.14*

