#include "bille.h"
#include "u1-interface.h"
#include "u5-parametres.h"
#include "u4-fonctions.h"
#include "math.h"
#include <FL/Fl_GIF_Image.H>
#include <FL/Fl.H>
#include <FL/fl_draw.H>

bille::bille(/*char* imgPath*/) : m_rayon(12), m_x_pos(L_ZONE-12), m_y_pos(H_ZONE-12-5), m_x_vit(0), m_y_vit(0) //, m_img(imgPath)
{
    //ctor
}

bille::~bille()
{
    //dtor
}

/*bille::bille(const bille& other)
{
    //copy ctor
}*/

float bille::get_x_pos() const
{
    return m_x_pos;
}
float bille::get_y_pos() const
{
    return m_y_pos;
}
float bille::get_x_vit() const
{
    return m_x_vit;
}
float bille::get_y_vit() const
{
    return m_y_vit;
}
void bille::chg_x_pos(float nXpos)
{
    m_x_pos=nXpos;
}
void bille::chg_y_pos(float nYpos)
{
    m_y_pos=nYpos;
}
void bille::rebond()
{
    if ( m_x_pos >= L_ZONE-m_rayon)
    {
        m_y_pos = L_ZONE-m_rayon ;
        m_x_vit = -1 *COEFF_PERTES* m_x_vit ;
    }

    if ( m_y_pos >= H_ZONE-m_rayon)
    {
        m_y_pos = H_ZONE-m_rayon ;
        m_y_vit = -1 *COEFF_PERTES* m_y_vit ;
    }

    if ( m_x_pos <= m_rayon)
    {
        m_x_pos = m_rayon ;
        m_x_vit = -1*COEFF_PERTES * m_x_vit ;
    }

    if ( m_y_pos <= m_rayon)
    {
        m_y_pos = m_rayon ;
        m_y_vit = -1*COEFF_PERTES * m_y_vit ;
    }
}
void bille::move()
{
    m_x_pos = m_x_pos + m_x_vit*DUREE_CYCLE;
    m_y_pos = m_y_pos + m_y_vit - sin(INCLINAISON)/2*GRAVITE*DUREE_CYCLE*DUREE_CYCLE;
    m_x_vit = m_x_vit;
    m_y_vit = m_y_vit + sin(INCLINAISON)*GRAVITE*DUREE_CYCLE;
}
void bille::trace()
{
    /*if ( m_x_pos >= L_ZONE-m_rayon)
    {
        m_y_pos = L_ZONE-m_rayon ;
        m_x_vit = -1 *COEFF_PERTES* m_x_vit ;
    }

    if ( m_y_pos >= H_ZONE-m_rayon)
    {
        m_y_pos = H_ZONE-m_rayon ;
        m_y_vit = -1 *COEFF_PERTES* m_y_vit ;
    }

    if ( m_x_pos <= m_rayon)
    {
        m_x_pos = m_rayon ;
        m_x_vit = -1*COEFF_PERTES * m_x_vit ;
    }

    if ( m_y_pos <= m_rayon)
    {
        m_y_pos = m_rayon ;
        m_y_vit = -1*COEFF_PERTES * m_y_vit ;
    }
    m_x_pos = m_x_pos + m_x_vit*DUREE_CYCLE;
    m_y_pos = m_y_pos + m_y_vit - sin(INCLINAISON)/2*GRAVITE*DUREE_CYCLE*DUREE_CYCLE;
    m_x_vit = m_x_vit;
    m_y_vit = m_y_vit + sin(INCLINAISON)*GRAVITE*DUREE_CYCLE;*/
    Fl_GIF_Image Imagebille("media/bille.gif") ;
    Imagebille.draw(X_ZONE + m_x_pos - m_rayon, Y_ZONE + m_y_pos - m_rayon);

}
