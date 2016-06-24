#ifndef TTREE_H
#define TTREE_H
#include "Strategy/boxperturber.h"
#include "ContourStructure/contourstructurefactory.h"

class TTree;

class TNode{
private:
    friend class TTree;
    int id;
    TNode *left, *mid, *right;
    TNode *par;
    TNode(int id): id(id) { }
    TNode*& getSon(int d){
        if(d == 0)
            return left;
        if(d == 1)
            return mid;
        return right;
    }
};

class TTree : public BoxPerturber{
public:
    BoxPackage getBoxPackage() ;
    void perturb(double degree) ;
    TTree(const TTree& b);
    TTree(ContourStructureFactory* contour_factory, const std::vector<Box>& boxes);
    ~TTree();
private:

    std::vector<Box> m_boxes;
    TNode* root;

    void randomInsert(int id);
    void insertAt(TNode* cur, TNode* node, int d);
    void remove(TNode* node);
    int randomRemove();
    void randomMove();
    void randomSwap();
    TNode* randomReplaceRoot(TNode* node);
    int randAvailableId();
    TNode*& getConnection(TNode* cur);

    void decompose(TNode* cur, bool new_tree, int t_val, std::vector<std::pair<TNode*, int> >& btrees);
    void clear(TNode* cur);

    std::vector<TNode*> node_map;
//    void fill() ;
//    void clear() ;
    // Need Implemention
};

#endif // TTREE_H
