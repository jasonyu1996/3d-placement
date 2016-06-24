#ifndef BOXPERTURBERFACTORY_H
#define BOXPERTURBERFACTORY_H

#include "boxperturber.h"

class BoxPerturberFactory{
public:
    virtual ~BoxPerturberFactory() {}
    virtual BoxPerturber* getBoxPerturber(const std::vector<Box>& boxes) = 0;
};

#endif // BOXPERTURBERFACTORY_H
