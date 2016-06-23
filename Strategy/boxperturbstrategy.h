#ifndef BOXPERTURBSTRATEGY_H
#define BOXPERTURBSTRATEGY_H
#include "kernel.h"

class BoxPerturbStrategy {
public:
    virtual ~BoxPerturbStrategy() ;
    virtual void getBoxPackege(const BoxPackage& boxpackage) = 0;
    virtual void perturb(double degree) = 0 ;
    virtual void fill() = 0 ;
    virtual void clear() = 0 ;
};

#endif // BOXPERTURBSTRATEGY_H
