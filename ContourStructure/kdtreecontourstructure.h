#ifndef KDTREECONTOURSTRUCTURE_H
#define KDTREECONTOURSTRUCTURE_H

#include "contourstructure.h"
#include <cstddef>
#include "kernel.h"

class KDTreeContourStructure : public ContourStructure {
public:
    KDTreeContourStructure(int n=-INF, int m=INF);
	~KDTreeContourStructure();
	int Update(int x1, int y1, int x2, int y2, int add);
private:
	struct KDNode {
		int x1, x2, y1, y2;
		bool dtype;
		int tag;
		int maxv;
		KDNode *ls;
		KDNode *rs;
		KDNode(int x1, int x2, int y1, int y2, bool dtype):
			x1(x1), x2(x2), y1(y1), y2(y2), dtype(dtype) {
				tag = -1;
				maxv = 0;
				ls = NULL;
				rs = NULL;
			}
	} *root;
	void KDPush(KDNode *p);
	int KDQuery(KDNode *p, int x1, int y1, int x2, int y2);
	void KDModify(KDNode *p, int x1, int y1, int x2, int y2, int val);
	void KDDestory(KDNode *p);
};

#endif // KDTREECONTOURSTRUCTURE_H
