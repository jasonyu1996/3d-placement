#ifndef TTREE_H
#define TTREE_H
#include "Strategy/boxperturber.h"

class TTree;

class TNode{
private:
    friend class TTree;
    int id;
    TNode *left, *mid, *right;
    TNode *par;
};

class TTree : public BoxPerturber{
public:
    void getBoxPackage() ;
    void perturb(double degree) ;
    TTree(const TTree& b);
    TTree(ContourStructureFactory* contour_factory, const std::vector<Box>& boxes);
    ~TTree();
private:

    std::vector<Box> m_boxes;
    TNode* root;

    void randomInsert(TNode* cur, int id);
    void randomInsert(int id);

    void decompose(TNode* cur, bool new_tree, int t_val, std::vector<std::pair<TNode*, int> >& btrees);
    void clear(TNode* cur);


//    void fill() ;
//    void clear() ;
    // Need Implemention
};

#endif // TTREE_H
