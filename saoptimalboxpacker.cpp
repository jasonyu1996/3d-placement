#include "kernel.h"
#include "saoptimalboxpacker.h"

using namespace std ;
typedef long long LL ;

int SAOptimalBoxPacker::packBoxes(const std::vector<Box>& box, BoxPackage& answer)
{
    ofstream os("Debug.txt") ;
    BoxPerturber* perturber = PS->getBoxPerturber(box) ;
    int mn = INF, tp ;
    BoxPackage temp ;
    for(int i = 0; i < 100000; i ++)
    {
        perturber->perturb(Random(10, 1)/10.0);
        temp = perturber->getBoxPackage() ;
        tp = VS->getWeight(temp) ;
        os << mn << " " << tp << endl ;
        if(mn > tp)
            mn = tp, answer = temp ;
    }
    return mn ;
}
