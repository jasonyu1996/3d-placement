#define DEBUGMODE

#include "kernel.h"
#include "boxpacker.h"
#include "saoptimalboxpacker.h"

#include "ContourStructure/contourstructure.h"
#include "ContourStructure/naivecontourstructure.h"
#include "ContourStructure/contourstructurefactory.h"
#include "ContourStructure/naivecontourstructurefactory.h"
#include "ContourStructure/kdtreecontourstructure.h"
#include "ContourStructure/kdtreecontourstructurefactory.h"

#include "Strategy/boxpackagevaluestrategy.h"
#include "Strategy/boxvolume.h"
#include "Strategy/boxperturber.h"
#include "Strategy/boxperturberfactory.h"
#include "Strategy/ttree.h"
#include "Strategy/ttreefactory.h"

using namespace std ;
typedef long long LL ;

vector<Box> box ;
BoxPackage answer ;
string input, output ;

int main()
{

#ifndef DEBUGMODE
    cin >> input ;
    cin >> output ;
#else
    input = "Input.txt" ;
    output = "Output.txt" ;
#endif

    ifstream is(input.c_str()) ;
    ofstream os(output.c_str()) ;

    srand(time(0)) ;
    Box b ;
    while(is >> b) box.push_back(b) ;

    SAOptimalConfig conf = SAOptimalConfig() ;
    NaiveContourStructureFactory naive = NaiveContourStructureFactory() ;
    SAOptimalBoxPacker SA(new TTreeFactory(&naive), new BoxVolume(), &conf) ;
    SA.packBoxes(box, answer);

    os << answer ;

    return 0 ;
}
