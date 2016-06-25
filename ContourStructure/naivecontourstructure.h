#ifndef NAIVECONTOURSTRUCTURE_H
#define NAIVECONTOURSTRUCTURE_H

#include "contourstructure.h"

class NaiveContourStructure : public ContourStructure {
public:
    NaiveContourStructure(int n, int m) ; // n,m is the size of matrix
    int Update(int x1, int y1, int x2, int y2, int add) ;
    // Need Implemention
    NaiveContourStructure(int n=0, int m=0); // n,m is the size of matrix
    ~NaiveContourStructure();
    int Update(int x1, int y1, int x2, int y2, int add);
private:
	int n, m;
	int *grid;
};

#endif // NAIVECONTOURSTRUCTURE_H
