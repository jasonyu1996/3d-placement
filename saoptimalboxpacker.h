#ifndef SAOPTIMALBOXPACKER_H
#define SAOPTIMALBOXPACKER_H
#include "boxpacker.h"
#include "Strategy/boxpackagevaluestrategy.h"
#include "Strategy/boxperturbstrategy.h"
#include "Strategy/boxvolume.h"
#include "Strategy/ttree.h"

class SAOptimalConfig {
    // Need Implemention
};

class SAOptimalBoxPacker : public BoxPacker {
public:
    BoxPerturbStrategy* PS ;
    BoxPackageValueStrategy* VS ;
    SAOptimalConfig* Config ;
    SAOptimalBoxPacker(BoxPerturbStrategy* PS = new TTree(),
                       BoxPackageValueStrategy* VS = new BoxVolume(),
                       SAOptimalConfig* Config = new SAOptimalConfig()
                       ) : PS(PS), VS(VS), Config(Config) {}
    // Need Implemention
};

#endif // SAOPTIMALBOXPACKER_H
