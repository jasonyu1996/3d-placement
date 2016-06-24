#ifndef CONTOURSTRUCTUREFACTORY_H
#define CONTOURSTRUCTUREFACTORY_H

#include "contourstructure.h"

class ContourStructureFactory{
public:
    virtual ~ContourStructureFactory() {}
    virtual ContourStructure* getContourStructure() = 0;
};

#endif // CONTOURSTRUCTUREFACTORY_H
