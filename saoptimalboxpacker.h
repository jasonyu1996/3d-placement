#ifndef SAOPTIMALBOXPACKER_H
#define SAOPTIMALBOXPACKER_H
#include "boxpacker.h"
#include "Strategy/boxpackagevaluestrategy.h"
#include "Strategy/boxperturber.h"
#include "Strategy/boxperturberfactory.h"
#include "Strategy/boxvolume.h"
#include "Strategy/ttree.h"
#include "Strategy/ttreefactory.h"
#include "ContourStructure/naivecontourstructurefactory.h"

class SAOptimalConfig {
    // Need Implemention
};

class SAOptimalBoxPacker : public BoxPacker {
public:
    BoxPerturberFactory* PS ;
    BoxPackageValueStrategy* VS ;
    SAOptimalConfig* Config ;
    SAOptimalBoxPacker(BoxPerturberFactory* PS,
                       BoxPackageValueStrategy* VS,
                       SAOptimalConfig* Config
                       ) : PS(PS), VS(VS), Config(Config) {}
     void packBoxes(const std::vector<Box>& box, BoxPackage& answer) ;
     // Need Implemention
};

#endif // SAOPTIMALBOXPACKER_H
