#ifndef BOXPERTURBSTRATEGY_H
#define BOXPERTURBSTRATEGY_H

class BoxPerturbStrategy {
    virtual getBoxPackege() = 0;
    virtual perturb(double degree) = 0 ;
    virtual fill() = 0 ;
    virtual clear() = 0 ;
};

#endif // BOXPERTURBSTRATEGY_H
