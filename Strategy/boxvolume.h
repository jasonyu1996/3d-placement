#ifndef BOXVOLUME_H
#define BOXVOLUME_H
#include "Strategy/boxpackagevaluestrategy.h"

class BoxVolume : public BoxPackageValueStrategy {
    int64 getWeight(const BoxPackage& boxpackage) ;
    // Need Implemention
};

#endif // BOXVOLUME_H
