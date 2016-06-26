#include "kernel.h"
#include "saoptimalboxpacker.h"
#include <cmath>

using namespace std ;
typedef long long LL ;

double SAOptimalConfig::accProb (double oldCost, double newCost, double T)
{
    return exp((oldCost - newCost)/T);
}

long long SAOptimalBoxPacker::packBoxes(const std::vector<Box>& box, BoxPackage& answer)
{
    ofstream os("Debug.txt") ;
    BoxPerturber* bestPerturber = PS->getBoxPerturber(box) ;
    
    long long bestCost, tCost ; // bestCost storesthe best cost of the packging, tCost is the temporary
    BoxPackage tPackage; // bestPackage storesthe best cost of the packging, tPackage is the temporary
    
    ///
    double T = Config->T; //starting temperature
    double T_min = Config->T_min;  //minimum temperature at which process stops
    double alpha = Config->alpha ;//increment the temperature
    ///
    
    tPackage = bestPerturber->getBoxPackage() ;
    bestCost = VS->getWeight(tPackage) ;

    while (T > T_min)
    {
        for(int i = 0; i < 100; i ++)
        {
            BoxPerturber* tPerturber = bestPerturber->clone() ;
            tPerturber->perturb(T/2);
            tPackage = tPerturber->getBoxPackage() ;
            tCost = VS->getWeight(tPackage) ;

#ifdef DEBUGMODE
            os << bestCost << " " << tCost << endl ;
#endif

            if(tCost < bestCost)
            {    
                bestCost = tCost;
                bestPerturber = tPerturber ;
            }
            else
            {
                if(Config->accProb(bestCost, tCost, T) > Random(1000000000, 0)/1000000000.0)
                {   
                    bestCost = tCost;
                    bestPerturber = tPerturber ;
                }   
            }
            
            delete tPerturber ;
        }
        T *= alpha;
    }
    answer = bestPerturber->getBoxPackage() ;
    return bestCost;
}
