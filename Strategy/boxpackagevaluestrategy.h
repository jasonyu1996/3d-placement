#ifndef BOXPACKAGEVALUESTRATEGY_H
#define BOXPACKAGEVALUESTRATEGY_H
#include "kernel.h"

class BoxPackageValueStrategy {
public:
    virtual ~BoxPackageValueStrategy() ;
    virtual int64 getWeight(const BoxPackage& boxpackage) = 0 ;
};

#endif // BOXPACKAGEVALUESTRATEGY_H
