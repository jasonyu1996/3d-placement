#ifndef BOXPACKER_H
#define BOXPACKER_H
#include "kernel.h"

class BoxPacker {
public:
    virtual ~BoxPacker() { }
    virtual long long packBoxes(const std::vector<Box>& box, BoxPackage& answer) = 0 ;
};

#endif // BOXPACKER_H
