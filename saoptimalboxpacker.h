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
public:
    double T, T_min, alpha, gamma ;
    SAOptimalConfig(double T=1.0, double T_min=0.000001, double alpha=0.9, double gamma=0.01) : T(T), T_min(T_min), alpha(alpha), gamma(gamma) {}
    double accProb(double, double, double); //calculates acceptance probability for SA algorithm
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
     long long packBoxes(const std::vector<Box>& box, BoxPackage& answer) ;
};

#endif // SAOPTIMALBOXPACKER_H
