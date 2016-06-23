#ifndef KERNEL_H
#define KERNEL_H

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <cassert>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>

#define Random(xx, yy) (rand()%(xx)+(yy))
#define Inf 0x7ffffff

typedef int int32 ;
typedef long long int64 ;

// -----------------------Class Box--------------------------

class Box {
public:
    int32 T, X, Y ;
    Box(int T=0, int X=0, int Y=0):T(T), X(X), Y(Y) {}
    int64 getVolume() {return (int64)T*X*Y ;}
    void randomRotate() ;
};
inline void Box::randomRotate()
{
    if(Random(2, 0)) std::swap(T, X) ;
    if(Random(2, 0)) std::swap(X, Y) ;
    if(Random(2, 0)) std::swap(T, Y) ;
}

// ---------------------Class Point-------------------------

class Point {
public:
    int32 x, y, z ;
    Point(int x=0, int y=0, int z=0) : x(x), y(y), z(z) {}
    bool operator < (Point b) const {return x < b.x || (x == b.x && (y < b.y || (y == b.y && z < b.z))) ;}
    Point operator + (Point b) const {return Point(x+b.x, y+b.y, z+b.z) ;}
    Point operator - (Point b) const {return Point(x-b.x, y-b.y, z-b.z) ;}
    Point operator * (int32 b) const {return Point(x*b, y*b, z*b) ;}
};

// ---------------------Class PlacedBox---------------------

class PlacedBox : public Box {
public:
    Point origin ;
    PlacedBox(Box box=Box(), Point origin=Point()) : Box(box), origin(origin) {}
    Point getDiagonalPointA() {return origin ;}
    Point getDiagonalPointB() {return origin+Point(T, X, Y) ;}
};

// ---------------------Class BoxPackage---------------------

class BoxPackage {
public:
    std::vector<PlacedBox> Boxes ;
    void add(PlacedBox b) {Boxes.push_back(b) ;}
    void getBoundingBox() ;
    bool PackageisLegal() ; // Need Implemention
    int64 GetVolume() ;
};
inline void BoxPackage::getBoundingBox()
{
    Point dig1 = Point(Inf, Inf), dig2 = Point(-Inf, -Inf) ;
    for(int32 i = 0; i < Boxes.size(); i ++)
    {
        dig1.x = std::min(dig1.x, Boxes[i].origin.x) ;
        dig1.y = std::min(dig1.y, Boxes[i].origin.y) ;
        dig2.x = std::max(dig2.x, Boxes[i].getDiagonalPointB().x) ;
        dig2.y = std::max(dig2.y, Boxes[i].getDiagonalPointB().y) ;
    }
}
inline int64 BoxPackage::GetVolume()
{
    int64 sum = 0 ;
    for(int32 i = 0; i < Boxes.size(); i ++)
        sum += Boxes[i].getVolume() ;
    return sum ;
}

#endif // KERNEL_H
