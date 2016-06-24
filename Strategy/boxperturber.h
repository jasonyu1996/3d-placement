#ifndef BOXPERTURBER_H
#define BOXPERTURBER_H
#include "kernel.h"

class BoxPerturber {
public:
    virtual ~BoxPerturber() ;
    virtual BoxPackage getBoxPackage() = 0;
    virtual void perturb(double degree) = 0 ;
};

#endif // BOXPERTURBER_H
