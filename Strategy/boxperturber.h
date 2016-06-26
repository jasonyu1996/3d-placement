#ifndef BOXPERTURBER_H
#define BOXPERTURBER_H
#include "kernel.h"

class BoxPerturber {
public:
    virtual ~BoxPerturber() { }
    virtual BoxPackage getBoxPackage() {return BoxPackage() ;}
    virtual void perturb(double degree) {} ;
};

#endif // BOXPERTURBER_H
