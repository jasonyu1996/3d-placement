#ifndef NAIVECONTOURSTRUCTUREFACTORY_H
#define NAIVECONTOURSTRUCTUREFACTORY_H

#include "contourstructurefactory.h"
#include "naivecontourstructure.h"

class NaiveContourStructureFactory: public ContourStructureFactory{
public:
    NaiveContourStructure* getContourStructure(){
        return new NaiveContourStructure();
    }
};

#endif // NAIVECONTOURSTRUCTUREFACTORY_H
