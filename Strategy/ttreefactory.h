#ifndef TTREEFACTORY_H
#define TTREEFACTORY_H

#include "boxperturberfactory.h"
#include "ttree.h"
#include "../ContourStructure/contourstructurefactory.h"

class TTreeFactory: public BoxPerturberFactory{
public:
    ContourStructureFactory* contour_factory ;
    TTreeFactory(ContourStructureFactory* contour_factory);
    TTree* getBoxPerturber(const std::vector<Box>& boxes){
        return new TTree(contour_factory, boxes);
    }
};

#endif // TTREEFACTORY_H
