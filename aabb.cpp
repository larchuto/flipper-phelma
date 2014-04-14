#include "aabb.h"

aabb::aabb(int xsize, int ysize) : m_xsize(xsize), m_ysize(ysize)
{

}

aabb::~aabb()
{

}

void trace();
{

}

bool touche(int x, int y);
{
    if ((x>=m_x_pos-xsize/2 && x<=m_x_pos+xsize/2) && (y>=m_y_pos-ysize/2 && y<=m_y_pos+ysize/2))
    {
        return true;
    }
    return false;
}
