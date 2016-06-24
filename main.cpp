#define DEBUGMODE

#include "kernel.h"
#include "ContourStructure/contourstructure.h"
#include "ContourStructure/naivecontourstructure.h"
#include "ContourStructure/segmentree.h"
#include "Strategy/boxpackagevaluestrategy.h"
#include "Strategy/boxperturber.h"
#include "Strategy/boxvolume.h"
#include "Strategy/ttree.h"
#include "boxpacker.h"
#include "saoptimalboxpacker.h"

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

    ifstream is(input) ;
    ofstream os(output) ;

    Box b ;
    while(is >> b) box.push_back(b) ;
    SAOptimalConfig conf = SAOptimalConfig() ;
    NaiveContourStructureFactory naive = NaiveContourStructureFactory() ;
    SAOptimalBoxPacker SA(new TTreeFactory(&naive), new BoxVolume(), &conf) ;
    SA.packBoxes(box, answer);

    os << answer ;

    return 0 ;
}
