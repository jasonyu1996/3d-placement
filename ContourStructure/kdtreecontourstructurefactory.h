#ifndef KDTREECONTOURSTRUCTUREFACTORY_H
#define KDTREECONTOURSTRUCTUREFACTORY_H

#include "contourstructurefactory.h"
#include "kdtreecontourstructure.h"

class KDTreeContourStructureFactory: public ContourStructureFactory{
public:
    KDTreeContourStructure* getContourStructure(){
        return new KDTreeContourStructure();
    }
};

#endif // KDTREECONTOURSTRUCTUREFACTORY_H
