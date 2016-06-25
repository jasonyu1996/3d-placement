#ifndef TTREEFACTORY_H
#define TTREEFACTORY_H

#include "boxperturberfactory.h"
#include "ttree.h"
#include "../ContourStructure/contourstructurefactory.h"

class TTreeFactory: public BoxPerturberFactory{
public:
    TTreeFactory(ContourStructureFactory* contour_factory): m_factory(contour_factory) {}
    TTree* getBoxPerturber(const std::vector<Box>& boxes){
        return new TTree(m_factory, boxes);
    }
private:
    ContourStructureFactory* m_factory;
};

#endif // TTREEFACTORY_H
