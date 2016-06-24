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

// -----------------------Class Box--------------------------

class Box {
public:
    int T, X, Y ;
    Box(int T=0, int X=0, int Y=0):T(T), X(X), Y(Y) {}
    long long getVolume() {return (long long)T*X*Y ;}
    void randomRotate() ;
    friend std::istream& operator >> (std::istream& is, Box box) ;
};
inline void Box::randomRotate()
{
    if(Random(2, 0)) std::swap(T, X) ;
    if(Random(2, 0)) std::swap(X, Y) ;
    if(Random(2, 0)) std::swap(T, Y) ;
}
std::istream& operator >> (std::istream& is, Box box)
{
    is >> box.T >> box.X >> box.Y ;
    return is ;
}

// ---------------------Class Point-------------------------

class Point {
public:
    int x, y, z ;
    Point(int x=0, int y=0, int z=0) : x(x), y(y), z(z) {}
    bool operator < (Point b) const {return x < b.x || (x == b.x && (y < b.y || (y == b.y && z < b.z))) ;}
    Point operator + (Point b) const {return Point(x+b.x, y+b.y, z+b.z) ;}
    Point operator - (Point b) const {return Point(x-b.x, y-b.y, z-b.z) ;}
    Point operator * (int b) const {return Point(x*b, y*b, z*b) ;}
    friend std::ostream& operator << (std::ostream& os, Point point) ;
};
std::ostream& operator << (std::ostream& os, Point point)
{
    os << "(" << point.x << "," << point.y << "," << point.z << ")" ;
    return os ;
}

// ---------------------Class PlacedBox---------------------

class PlacedBox : public Box {
public:
    Point origin ;
    PlacedBox(Box box=Box(), Point origin=Point()) : Box(box), origin(origin) {}
    PlacedBox(Point ga, Point gb) : origin(ga), Box((gb-ga).x, (gb-ga).y, (gb-ga).z) {}
    Point getDiagonalPointA() {return origin ;}
    Point getDiagonalPointB() {return origin+Point(T, X, Y) ;}
    friend std::ostream& operator << (std::ostream& os, PlacedBox box) ;
};
std::ostream& operator << (std::ostream& os, PlacedBox box)
{
    os << "A Placed Box: " << box.getDiagonalPointA()
       << " ---- " << box.getDiagonalPointB() << std::endl ;
    return os ;
}

// ---------------------Class BoxPackage---------------------

class BoxPackage {
public:
    std::vector<PlacedBox> Boxes ;
    void add(PlacedBox b) {Boxes.push_back(b) ;}
    PlacedBox getBoundingBox() ;
    bool PackageisLegal() ;
    long long GetVolume() ;
    friend std::ostream& operator << (std::ostream& os, BoxPackage boxpackage) ;
};
inline PlacedBox BoxPackage::getBoundingBox()
{
    Point dig1 = Point(Inf, Inf), dig2 = Point(-Inf, -Inf) ;
    for(int i = 0; i < Boxes.size(); i ++)
    {
        dig1.x = std::min(dig1.x, Boxes[i].origin.x) ;
        dig1.y = std::min(dig1.y, Boxes[i].origin.y) ;
        dig1.z = std::min(dig1.z, Boxes[i].origin.z) ;
        dig2.x = std::max(dig2.x, Boxes[i].getDiagonalPointB().x) ;
        dig2.y = std::max(dig2.y, Boxes[i].getDiagonalPointB().y) ;
        dig2.z = std::max(dig2.z, Boxes[i].getDiagonalPointB().z) ;
    }
    return PlacedBox(dig1, dig2) ;
}
inline long long BoxPackage::GetVolume()
{
    long long sum = 0 ;
    for(int i = 0; i < Boxes.size(); i ++)
        sum += Boxes[i].getVolume() ;
    return sum ;
}


#endif // KERNEL_H
