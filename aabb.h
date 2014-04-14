#ifndef DEF_AABB
#define DEF_AABB

#include "obstacle.h"

using namespace std;

class aabb : public obstacle
{
    public:
        aabb();
        void trace();
        bool touche(int x, int y);
    private:
        int m_xsize;
        int m_ysize;

}
