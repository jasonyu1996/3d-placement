#include "kdtreecontourstructure.h"
#include <algorithm>

using namespace std;

inline void upmax(int &a, int b) {
	if (b > a) a = b;
}

inline bool Contain(int x1, int x2, int y1, int y2) {
	return x1 <= y1 && y2 <= x2;
}

inline bool Intersect(int x1, int x2, int y1, int y2) {
	return !(x2 <= y1 || y2 <= x1);
}

KDTreeContourStructure::KDTreeContourStructure(int n, int m) {
	++n, ++m;
	root = new KDNode(0, n, 0, m, 0);
}

KDTreeContourStructure::~KDTreeContourStructure() {
	KDDestory(root);
}

int KDTreeContourStructure::Update(int x1, int y1, int x2, int y2, int add) {
	++x2, ++y2;
	// [a, b] -> [a, b)
	int maxv = KDQuery(root, x1, y1, x2, y2);
	maxv += add;
	KDModify(root, x1, y1, x2, y2, maxv);
	return maxv;
}

void KDTreeContourStructure::KDPush(KDNode *p) {
	if (p->ls == NULL) {
		if (p->x1 + 1 != p->x2 && p->dtype == 0) {
			int xm = (p->x1 + p->x2) / 2;
			p->ls = new KDNode(p->x1, xm, p->y1, p->y2, 1);
			p->rs = new KDNode(xm, p->x2, p->y1, p->y2, 1);
		} else {
			int ym = (p->y1 + p->y2) / 2;
			p->ls = new KDNode(p->x1, p->x2, p->y1, ym, 0);
			p->rs = new KDNode(p->x1, p->x2, ym, p->y2, 0);
		}
	}
	if (p->tag != -1) {
		p->ls->tag = p->ls->maxv = p->tag;
		p->rs->tag = p->rs->maxv = p->tag;
		p->tag = -1;
	}
}

int KDTreeContourStructure::KDQuery(KDNode *p, int x1, int y1, int x2, int y2) {
	if (p == NULL) return 0;
	if (Contain(x1, x2, p->x1, p->x2) && Contain(y1, y2, p->y1, p->y2)) {
		return p->maxv;
	}
	KDPush(p);
	KDNode *ls = p->ls;
	KDNode *rs = p->rs;
	int ret = 0;
	if (Intersect(x1, x2, ls->x1, ls->x2) && Intersect(y1, y2, ls->y1, ls->y2)) {
		upmax(ret, KDQuery(ls, x1, y1, x2, y2));
	}
	if (Intersect(x1, x2, rs->x1, rs->x2) && Intersect(y1, y2, rs->y1, rs->y2)) {
		upmax(ret, KDQuery(rs, x1, y1, x2, y2));
	}
	return ret;
}

void KDTreeContourStructure::KDModify(KDNode *p, int x1, int y1, int x2, int y2, int val) {
	if (Contain(x1, x2, p->x1, p->x2) && Contain(y1, y2, p->y1, p->y2)) {
		p->tag = p->maxv = val;
		return;
	}
	KDPush(p);
	KDNode *ls = p->ls;
	KDNode *rs = p->rs;
	if (Intersect(x1, x2, ls->x1, ls->x2) && Intersect(y1, y2, ls->y1, ls->y2)) {
		KDModify(ls, x1, y1, x2, y2, val);
	}
	if (Intersect(x1, x2, rs->x1, rs->x2) && Intersect(y1, y2, rs->y1, rs->y2)) {
		KDModify(rs, x1, y1, x2, y2, val);
	}
	p->maxv = max(ls->maxv, rs->maxv);
}

void KDTreeContourStructure::KDDestory(KDNode *p) {
	if (p == NULL) return;
	KDDestory(p->ls);
	KDDestory(p->rs);
	delete p;
}