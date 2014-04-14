#include "obstacle.h"

obstacle::obstacle(int xpos, int ypos) : m_x_pos(xpos), m_y_pos(ypos) //, m_img(imgPath)
{
    //ctor
}

obstacle::~obstacle()
{
    //dtor
}

/*obstacle::obstacle(const obstacle& other)
{
    //copy ctor
}*/

int obstacle::get_x_pos() const
{
    return m_x_pos;
}
int obstacle::get_y_pos() const
{
    return m_y_pos;
}
void obstacle::chg_x_pos(int nXpos)
{
    m_x_pos=nXpos;
}
void obstacle::chg_y_pos(int nYpos)
{
    m_y_pos=nYpos;
}
