#ifndef DOUBLELINK_H
#define DOUBLELINK_H
#include "ContourStructure/contourstructure.h"

class DoubleLink : public ContourStructure {
    DoubleLink(int n=0, int m=0) ; // n,m is the size of matrix
    int Update(int x1, int y1, int x2, int y2, int add) ;
    // Need Implemention
};

#endif // DOUBLELINK_H
