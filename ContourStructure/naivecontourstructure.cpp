#include "naivecontourstructure.h"
#include <algorithm>

inline bool intersect(int x11, int y11, int x12, int y12,
                      int x21, int y21, int x22, int y22){
    return std::max(x11, x21) < std::min(x12, x22) &&
            std::max(y11, y21) < std::min(y12, y22);
}


int NaiveContourStructure::Update(int x1, int y1, int x2, int y2, int add) {
    int n = (int)m_x1.size();
    int ans = 0;
    for(int i = 0; i < n; i ++)
        if(m_add[i] > ans && intersect(x1, y1, x2, y2, m_x1[i], m_y1[i], m_x2[i], m_y2[i]))
            ans = m_add[i];
    m_x1.push_back(x1);
    m_y1.push_back(y1);
    m_x2.push_back(x2);
    m_y2.push_back(y2);
    m_add.push_back(ans + add);

    return ans;
}
