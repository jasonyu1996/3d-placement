#include "ttree.h"

TTree::TTree(ContourStructureFactory *contour_factory, const std::vector<Box> &boxes): m_boxes(boxes), root(NULL),
    contour_factory(contour_factory), node_map((int)boxes.size()){
    std::random_shuffle(m_boxes.begin(), m_boxes.end());
    int n = (int)m_boxes.size();
    for(int i = 0; i < n; i ++)
        randomInsert(i);
    link_map = new Link*[n];
}

TTree::~TTree(){
    delete []link_map;
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

int TTree::appendLink(int fa, int id, int d){
    int t, tr;
    Link *st, *cur;
    if(fa == -1){ // empty linked list
        t = 0;
        st = base_link;
    }
    else if(d == 0){ // left child
        t = link_map[fa]->x + m_boxes[fa].T;
        st = link_map[fa]->nxt->nxt;
    } else{ // mid child
        t = link_map[fa]->x;
        st = link_map[fa];
    }
    tr = t + m_boxes[id].T;
    cur = st;
    int Y = 0;
    while(cur->nxt->x <= tr){
        if(cur->val > Y)
            Y = cur->val;
        cur = cur->nxt->nxt;
    }
    if(cur->x < tr && cur->val > Y)
        Y = cur->val;
    Link* he = newLink(t, Y + m_boxes[id].Y, id, true);
    Link* ta = newLink(tr, Y + m_boxes[id].Y, id, false);
    he->nxt = ta;
    ta->prev = he;

    he->prev = st->prev;
    if(he->prev != NULL)
        he->prev->nxt = he;
    Link* mi = newLink(tr, cur->val, cur->belong, false);
    mi->nxt = cur->nxt;
    mi->nxt->prev = mi;
    ta->nxt = mi;
    mi->prev = ta;

    return Y;
}

void TTree::placeBox(int fa, int id, int d, int t_offset, BoxPackage& pack){
    int y = appendLink(fa, id, d);
    int t = t_offset + link_map[id]->x;
    int x = contour->Update(t, y, t + m_boxes[id].T, y + m_boxes[id].Y, m_boxes[id].X);// temporarily for test
    pack.add(PlacedBox(Point(x, y, t),
                       Point(x + m_boxes[id].X, y + m_boxes[id].Y, t + m_boxes[id].T)));
}

void TTree::dfsBinaryTree(TNode *cur, int t_offset, BoxPackage& res){
    if(cur->left != NULL){
        placeBox(cur->id, cur->left->id, 0, t_offset, res);
        dfsBinaryTree(cur->left, t_offset, res);
    }
    if(cur->mid != NULL){
        placeBox(cur->id, cur->mid->id, 1, t_offset, res);
        dfsBinaryTree(cur->mid, t_offset, res);
    }
}


BoxPackage TTree::getBoxPackage(){
    BoxPackage res;

    decompose(root, true, 0, btrees);

    contour = contour_factory->getContourStructure();

    int m = (int)btrees.size();
    for(int i = 0; i < m; i ++){// for each binary tree
        //perform a depth first seach for the current binary tree
        //TODO
        base_link = newLink(0, 0, -1, false);
        base_link->nxt = newLink(INF, 0, -1, false);
        base_link->nxt->prev = base_link;

        placeBox(-1, btrees[i].first->id, 0, btrees[i].second, res);
//        link_map[btrees[i].first->id] = new Link(btrees[i].first, 0, btrees[i].first->id);
        dfsBinaryTree(btrees[i].first, btrees[i].second, res);

        //cleaning
        int linkn = (int)link_pool.size();
        for(int i = 0; i < linkn; i ++)
            delete link_pool[i];
        link_pool.clear();
    }

    delete contour;

    btrees.clear();
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
        if(nn != NULL)
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
    if(nroot != NULL)
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
    if((int)m_boxes.size() < 2)
        return;
    int ti = (int)(20 * degree);
    for(int i = 0; i < ti; i ++)
        if(rand() % 2)
            randomSwap();
        else
            randomMove();
}

TNode* TTree::cloneTree(TNode *cur, std::vector<TNode*>& node_map) const{
    if(cur == NULL)
        return NULL;
    TNode* nn = new TNode();
    nn->id = cur->id;
    node_map[nn->id] = nn;

    nn->left = cloneTree(cur->left, node_map);
    nn->mid = cloneTree(cur->mid, node_map);
    nn->right = cloneTree(cur->right, node_map);

    if(nn->left != NULL)
        nn->left->par = nn;
    if(nn->mid != NULL)
        nn->mid->par = nn;
    if(nn->right != NULL)
        nn->right->par = nn;

    return nn;
}

TTree* TTree::clone() const{
    TTree* res = new TTree();
    res->m_boxes = m_boxes;
    res->contour_factory = contour_factory;

    int n = (int)m_boxes.size();

    res->link_map = new Link*[n];

    res->node_map.resize(n);
    res->root = cloneTree(root, res->node_map);
    if(res->root != NULL)
        res->root->par = NULL;

    return res;
}
