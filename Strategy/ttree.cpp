#include "ttree.h"
#include<stack>

//static void linkAfter(){

//}

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

int TTree::appendLink(int fa, int id, int d, Link **link_map){
    if(fa == -1){ // empty linked list
        link_map[id] = new Link(0, 0, id);
        link_map[id]->nxt = new Link(m_boxes[id].T, 0, id);
        link_map[id]->nxt->prev = link_map[id];
        return 0;
    }
    int t;
    Link* cur;
    if(d == 0){
        t = link_map[fa]->x + m_boxes[fa].T;
        cur = link_map[fa]->nxt;
    } else{
        t = link_map[fa]->x;
        cur = link_map[fa]->nxt->nxt;
    }
}

void TTree::placeBox(int fa, int id, int d, int t_offset, Link **link_map, BoxPackage& pack){
    int y = appendLink(fa, id, d, link_map);
    int t = t_offset + link_map[id].x;
    int x = 0;// temporarily for test
    pack.add(PlacedBox(Point(x, y, t),
                       Point(x + m_boxes[id].X, y + m_boxes[id].Y, t + m_boxes[id].T)));
}

void TTree::dfsBinaryTree(TNode *cur, int t_offset, Link **link_map, BoxPackage& res){
    if(cur->left != NULL){
        placeBox(cur->id, cur->left->id, 0, t_offset, link_map, res);
        dfsBinaryTree(cur->left, t_offset, link_map, res);
    }
    if(cur->mid != NULL){
        placeBox(cur->id, cur->mid->id, 1, t_offset, link_map, res);
        dfsBinaryTree(cur->mid, t_offset, link_map, res);
    }
}


BoxPackage TTree::getBoxPackage(){
    BoxPackage res;
    static std::vector<std::pair<TNode*, int> > btrees;

    int n = (int)m_boxes.size();

    decompose(root, 0, true, btrees);

//    ContourStructure* contour = contour_factory->getContourStructure();
    static std::vector<Link*> link_pool;
    Link* link_map = new Link*[n];


    int m = (int)btrees.size();
    for(int i = 0; i < m; i ++){// for each binary tree
        //perform a depth first seach for the current binary tree
        //TODO
        placeBox(-1, btrees[i].first->id, 0, btrees[i].second, link_map, res);
//        link_map[btrees[i].first->id] = new Link(btrees[i].first, 0, btrees[i].first->id);
        dfsBinaryTree(btrees[i].first, btrees[i].second, link_map, res);

        //cleaning
        int linkn = (int)link_pool.size();
        for(int i = 0; i < linkn; i ++)
            delete link_pool[i];
        link_pool.clear();
    }


    delete []link_map;
    btree.clear();
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
