#ifndef NAIVECONTOURSTRUCTURE_H
#define NAIVECONTOURSTRUCTURE_H

#include "contourstructure.h"
#include<vector>

class NaiveContourStructure : public ContourStructure {
public:
    int Update(int x1, int y1, int x2, int y2, int add);
private:
    std::vector<int> m_x1, m_y1, m_x2, m_y2, m_add;
};

#endif // NAIVECONTOURSTRUCTURE_H
