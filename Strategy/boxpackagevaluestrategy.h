#ifndef BOXPACKAGEVALUESTRATEGY_H
#define BOXPACKAGEVALUESTRATEGY_H
#include "kernel.h"

class BoxPackageValueStrategy {
public:
    virtual ~BoxPackageValueStrategy() ;
    virtual long long getWeight(const BoxPackage& boxpackage) = 0 ;
};

#endif // BOXPACKAGEVALUESTRATEGY_H
