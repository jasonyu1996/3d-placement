#include "kernel.h"
#include "saoptimalboxpacker.h"
#include <cmath>

using namespace std ;
typedef long long LL ;

double SAOptimalConfig::accProb (double oldCost, double newCost, double T)
{
    //if(T == 1) cout << gamma*(oldCost - newCost)/T << endl ;
    return exp(gamma*(oldCost - newCost)/T);
}

long long SAOptimalBoxPacker::packBoxes(const std::vector<Box>& box, BoxPackage& answer)
{
    ofstream os("Debug.txt") ;
    BoxPerturber  *bestPerturber = PS->getBoxPerturber(box), *returnPerturber ;
    
    long long bestCost, tCost, returnCost = (long long)INF*INF ; // bestCost storesthe best cost of the packging, tCost is the temporary
    BoxPackage tPackage; // bestPackage storesthe best cost of the packging, tPackage is the temporary
    
    ///
    ///
    for(int t = 0; t < 20; t ++)
    {
        //double T = 1, T_min = 0.0001, alpha = 0.992 ;
        double T = Config->T/(1+min(15, t)); //starting temperature
        double T_min = Config->T_min;  //minimum temperature at which process stops
        double alpha = Config->alpha ;//increment the temperature*/
        //bestPerturber->perturb(0.1) ;
        tPackage = bestPerturber->getBoxPackage() ;
        bestCost = VS->getWeight(tPackage) ;
        while (T > T_min)
        {
            double tmp = pow(T, 0.3) ;
            for(int i = 0; i < (t<=3?100:200); i ++)
            {
                BoxPerturber* tPerturber = bestPerturber->clone() ;
                tPerturber->perturb(tmp*0.5);
                tPackage = tPerturber->getBoxPackage() ;
                tCost = VS->getWeight(tPackage) ;

#ifdef DEBUGMODE
                os << bestCost << " " << tCost << " " << T << endl ;
#endif

                if(tCost < bestCost ||
                        Config->accProb(bestCost, tCost, T) > Random(1000000000, 0)/1000000000.0)
                {
                    bestCost = tCost;
                    delete bestPerturber;
                    bestPerturber = tPerturber ;
                } else{
                    delete tPerturber;
                }

            }
            T *= alpha;
        }
        if(returnCost > bestCost)
        {
            if(returnCost != (long long)INF*INF)
                delete returnPerturber ;
            returnPerturber = bestPerturber ;
            bestPerturber = bestPerturber->clone() ;
            returnCost = bestCost ;

        }
        else
        {
            delete bestPerturber ;
            bestPerturber = returnPerturber->clone() ;
        }
    }
    answer = returnPerturber->getBoxPackage() ;
    return returnCost ;
}
