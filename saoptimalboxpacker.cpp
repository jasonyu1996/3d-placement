#include "kernel.h"
#include "saoptimalboxpacker.h"

using namespace std ;
typedef long long LL ;

int SAOptimalBoxPacker::packBoxes(const std::vector<Box>& box, BoxPackage& answer)
{
    ofstream os("Debug.txt") ;
    BoxPerturber* perturber = PS->getBoxPerturber(box) ;
    
    int bestCost = INF, tCost ; // bestCost storesthe best cost of the packging, tCost is the temporary
    BoxPackage bestPackage, tPackage; // bestPackage storesthe best cost of the packging, tPackage is the temporary
    
    ///
    double T = 1.0; //starting temperature
    double T_min = 0.000001;  //minimum temperature at which process stops
    double alpha = 0.9 //increment the temperature
    ///
    
    while (T > T_min)
    {
        for(int i = 0; i < 100; i ++)
        {
            perturber->perturb(Random(10, 1)/10.0);
            tPackage = perturber->getBoxPackage() ;
            tCost = VS->getWeight(tPackage) ;
            os << bestCost << " " << tCost << endl ;
            
            if(tCost < bestCost)
            {    
                bestCost = tCost; 
                bestPackage = tPackage;
                answer = bestPackage; 
            }
            else
            {
                if(Config->accProb(bestCost, tCost, T) > Random(1, 0))
                {   
                    bestCost = tCost; 
                    bestPackage = tPackage;
                }   
            }
            
        }
        T *= alpha;
    }
    return bestCost;
}
