#ifndef TTREE_H
#define TTREE_H
#include "Strategy/boxperturbstrategy.h"

class TTree : public BoxPerturbStrategy{
    void getBoxPackege(const BoxPackage& boxpackage) ;
    void perturb(double degree) ;
    void fill() ;
    void clear() ;
    // Need Implemention
};

#endif // TTREE_H
