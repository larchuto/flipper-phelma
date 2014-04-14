#include "aabb.h"

aabb::aabb()//int xsize, int ysize) : m_xsize(xsize), m_ysize(ysize)
{

}

aabb::~aabb()
{

}

void trace(int x_pos,int y_pos,int xsize, int ysize)
{
	m_xsize(xsize)=xsize; 
	m_ysize(ysize)=ysize;
	m_x_pos=x_pos;
	m_y_pos=y_pos;
}

bool touche(int x, int y)
{
    if ((x>=m_x_pos-xsize/2 && x<=m_x_pos+xsize/2) && (y>=m_y_pos-ysize/2 && y<=m_y_pos+ysize/2))
    {
        return true;
    }
    return false;
}
