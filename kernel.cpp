#include "kernel.h"
using namespace std ;
typedef long long LL ;

bool Intersect(int x1, int y1, int x2, int y2)
{
    if(x1 > x2) swap(x1, x2), swap(y1, y2) ;
    return y1 > x2 ;
}

bool BoxPackage::PackageisLegal()
{
    for(int i = 0; i < Boxes.size(); i ++)
        for(int j = i+1; j < Boxes.size(); j ++)
        {
            Point diga1 = Boxes[i].getDiagonalPointA() ;
            Point diga2 = Boxes[i].getDiagonalPointB() ;
            Point digb1 = Boxes[j].getDiagonalPointA() ;
            Point digb2 = Boxes[j].getDiagonalPointB() ;
            if(!Intersect(diga1.x, diga2.x, digb1.x, digb2.x)) continue ;
            if(!Intersect(diga1.y, diga2.y, digb1.y, digb2.y)) continue ;
            if(!Intersect(diga1.z, diga2.z, digb1.z, digb2.z)) continue ;
            return 0 ;
        }
    return 1 ;
}
ostream& operator << (ostream& os, BoxPackage boxpackage)
{
    os << "<--------Outputing an boxPackage------->" << endl ;
    os << endl ;

    long long V1, V2 ;
    os << "Volume of all boxes: " << (V1 = boxpackage.GetVolume()) << endl ;
    os << "Volume of bounding box: " << (V2 = boxpackage.getBoundingBox().getVolume()) << endl ;
    os << "Wasted volume: " << V2-V1 << "    with ratio: " << (double)(V2-V1)/V1 << endl ;
    os << endl ;

    for(int i = 0; i < boxpackage.Boxes.size(); i ++)
        os << boxpackage.Boxes[i] ;
    os << endl ;

    return os ;
}
