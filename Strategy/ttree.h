#ifndef TTREE_H
#define TTREE_H
#include "Strategy/boxperturber.h"
#include "ContourStructure/contourstructurefactory.h"


struct Link{
    Link *nxt, *prev;
    int x, val;
    int belong;
    Link(int x, int val, int belong): nxt(NULL), prev(NULL),
        x(x), val(val), belong(belong) {}
};


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
    ContourStructureFactory* contour_factory;

    void randomInsert(int id);
    void insertAt(TNode* cur, TNode* node, int d);
    void remove(TNode* node);
    int randomRemove();
    void randomMove();
    void randomSwap();
    TNode* randomReplaceRoot(TNode* node);
    int randAvailableId();
    TNode*& getConnection(TNode* cur);

    void placeBox(int fa, int id, int d, int t_offset, Link** link_map, BoxPackage& pack);
    void dfsBinaryTree(TNode* cur, int t_offset, Link** link_map, BoxPackage& pack);
    void decompose(TNode* cur, bool new_tree, int t_val, std::vector<std::pair<TNode*, int> >& btrees);
    void clear(TNode* cur);
    int appendLink(int fa, int id, int d, Link** link_map);

    std::vector<TNode*> node_map;
//    void fill() ;
//    void clear() ;
    // Need Implemention
};

#endif // TTREE_H
