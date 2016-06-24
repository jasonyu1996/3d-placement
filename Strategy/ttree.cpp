#include "ttree.h"
#include<stack>

TTree::TTree(ContourStructureFactory *contour_factory, const std::vector<Box> &boxes): m_boxes(boxes), root(NULL){
    std::random_shuffle(m_boxes.begin(), m_boxes.end());
    int n = (int)m_boxes.size();
    for(int i = 0; i < n; i ++)
        randomInsert(i);
}

TTree::~TTree(){
    clear(root);
}

void TTree::clear(TNode *cur){
    if(cur == NULL)
        return;
    clear(cur->left);
    clear(cur->mid);
    clear(cur->right);
    delete cur;
}

BoxPackage TTree::getBoxPackage(){
    BoxPackage res;
    static std::vector<std::pair<TNode*, int> > btrees;

    decompose(root, 0, true, btrees);

    int m = (int)btrees.size();
    for(int i = 0; i < m; i ++){// for each binary tree
        //perform a depth first seach for the current binary tree
        //TODO

    }
    return res;
}

void TTree::decompose(TNode* cur, bool new_tree, int t_val, std::vector<std::pair<TNode*, int> >& btrees){
    if(cur == NULL)
        return;
    if(new_tree)
        btrees.push_back(std::make_pair(cur, t_val));
    decompose(cur->left, false, t_val + m_boxes[cur->id].T, btrees);
    decompose(cur->mid, false, t_val, btrees);
    decompose(cur->right, true, t_val, btrees);
}

int TTree::randAvailableId(){
    int n = (int)node_map.size();
    int id;
    do
        id = rand() % n;
    while(node_map[id] == NULL);
    return id;
}

// insert node as the d-th son of cur
void TTree::insertAt(TNode *cur, TNode *node, int d){
    if(cur->getSon(d) == NULL){
        node->left = node->mid = node->right = NULL;
        node->par = cur;
        cur->getSon(d) = node;
    } else{
        node->getSon((d + 1) % 3) = node->getSon((d + 2) % 3) = NULL;
        node->getSon(d) = cur->getSon(d);
        node->getSon(d)->par = node;
        node->par = cur;
        cur->getSon(d) = node;
    }
}

void TTree::randomInsert(int id){
    TNode* node = new TNode(id);
    if(root == NULL){
        node->par = NULL;
        node->left = node->mid = node->right = NULL;
        root = node;
    } else{
        insertAt(node_map[randAvailableId()], node, rand() % 3);
    }
    node_map[id] = node;
}

TNode*& TTree::getConnection(TNode* node){
    if(node->par == NULL)
        return root;
    if(node == node->par->left)
        return node->par->left;
    if(node == node->par->mid)
        return node->par->mid;
    return node->par->right;
}

TNode* TTree::randomReplaceRoot(TNode *node){
    int nu[3];
    int cnt = 0;
    for(int i = 0; i < 3; i ++)
        if(node->getSon(i) != NULL)
            nu[cnt ++] = i;
    if(cnt == 0){
        return NULL;
    } else if(cnt == 1){
        return node->getSon(nu[0]);
    } else {
        int t = nu[rand() % cnt];
        TNode* nroot = node->getSon(t);
        TNode* nn= randomReplaceRoot(nroot);
        nroot->getSon(t) = nn;
        nn->par = nroot;
        for(int i = 0; i < 3; i ++)
            if(i != t){
                nroot->getSon(i) = node->getSon(i);
                if(nroot->getSon(i) != NULL)
                    nroot->getSon(i)->par = nroot;
            }
        return nroot;
    }
}

void TTree::remove(TNode* node){
    TNode* nroot = randomReplaceRoot(node);
    getConnection(node) = nroot;
    nroot->par = node->par;

    node_map[node->id] = NULL;
    delete node;
}

int TTree::randomRemove(){
//    int n = (int)node_map.size();
    int id = randAvailableId();
    remove(node_map[id]);
    return id;
}

// Perturbation type 1:
// randomly choose a node and change its position
void TTree::randomMove(){
    randomInsert(randomRemove());
}

// Perturbation type 2:
// randomly choose two nodes and swap them
void TTree::randomSwap(){
    int u = randAvailableId(), v = randAvailableId();
    std::swap(node_map[u], node_map[v]);
    std::swap(node_map[u]->id, node_map[v]->id);
}


void TTree::perturb(double degree){
    int ti = (int)(20 * degree);
    for(int i = 0; i < ti; i ++)
        if(rand() % 2)
            randomSwap();
        else
            randomMove();
}
