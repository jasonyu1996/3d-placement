#ifndef CONTOURSTRUCTURE_H
#define CONTOURSTRUCTURE_H

class ContourStructure {
public:
    virtual ~ContourStructure() {}
    virtual int Update(int x1, int y1, int x2, int y2, int add) = 0 ;
};

#endif // CONTOURSTRUCTURE_H
