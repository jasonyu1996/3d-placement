#ifndef BOXVOLUME_H
#define BOXVOLUME_H
#include "Strategy/boxpackagevaluestrategy.h"

class BoxVolume : public BoxPackageValueStrategy {
public:
    long long getWeight(const BoxPackage& boxpackage) ;
};

inline long long BoxVolume::getWeight(const BoxPackage& boxpackage)
{
    return boxpackage.getBoundingBox().getVolume() ;
}

#endif // BOXVOLUME_H
