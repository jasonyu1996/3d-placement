#ifndef BOXVOLUME_H
#define BOXVOLUME_H
#include "Strategy/boxpackagevaluestrategy.h"

class BoxVolume : public BoxPackageValueStrategy {
public:
    long long getWeight(const BoxPackage& boxpackage) ;
    // Need Implemention
};

#endif // BOXVOLUME_H
