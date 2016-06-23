# 3D-Placement

This is the team project for the OOP course. It tries to optimize the volume of the placement of a set of cubes.

## Interfaces

### Box

Defined with three edge lengths, `len0`, `len1` and `len2`. Note that a Box is independent of the order of these lengths, i.e, two Boxs are the same if and only if their corresponding edge lengths can be identical after being reordered arbitrarily.

* getVolume

### Point

Represented by its coordinates, i.e, the coordinates of the vector from the origin to it. The Point here lies in 3D space.

### OrientedBox

A Box with its orientation fixed. Note here that only those orientations where the edges are all parallel to coordinate axes are supported.

### PlacedBox

An OrientedBox with a specified position.

* getDiagonalPointA
* getDiagonalPointB

### BoxPackage

A set of PlacedBoxs.

* add: adding a placed cuboid
* getBoundingBox

### BoxPackageModel

Abstract

* fill
* clear
* getPlacedBoxSet
* perturb(double degree)

### TTree: BoxPackageModel

T-tree representation for a *compact* BoxPackage.

### BoxPacker

Abstract.

* packBoxes(const vector<Box>&)

### BoxPackageModelWeight 

Abstract.

* getWeight(const BoxPackageModel&)

### BoundingVolumeWeight: BoxPackageModelWeight

### SAOptimalBoxPacker: BoxPacker

Simulated Annealing algorithm.

* OptimalBoxPacker(BoxPackageModel, BoxPackageModelWeight)

## Reference

Yuh, Yang & Chang, 2009. T-Trees: A Tree-Based Representation for Temporal and Three-Dimensional Floorplanning. *ACM Transactions on Design Automation of Electronic Systems, Vol.14*

