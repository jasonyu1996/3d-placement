#ifndef NAIVECONTOURSTRUCTURE_H
#define NAIVECONTOURSTRUCTURE_H
#include "ContourStructure/contourstructure.h"

class NaiveContourStructure : public ContourStructure {
public:
    NaiveContourStructure(int n, int m) ; // n,m is the size of matrix
    int Update(int x1, int y1, int x2, int y2, int add) ;
    // Need Implemention
};

#endif // NAIVECONTOURSTRUCTURE_H
