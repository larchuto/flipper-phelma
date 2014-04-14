#ifndef DEF_AABB
#define DEF_AABB

#include "obstacle.h"

class aabb : public obstacle
{
    public:
        aabb();//int xsize, int ysize);
	~aabb();
        void trace(int xsize, int ysize);
        bool touche(int x, int y);
    private:
        int m_xsize;
        int m_ysize;

};

#endif
