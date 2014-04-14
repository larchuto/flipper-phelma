#ifndef BILLE_H
#define BILLE_H
#include <string>


class bille
{
    public:
        bille(/*std::string imgPath*/);
        virtual ~bille();
        //bille(const bille& other);
        float get_x_pos() const;
        float get_y_pos() const;
        float get_x_vit() const;
        float get_y_vit() const;
        void chg_x_pos(float nXpos);
        void chg_y_pos(float nYpos);
        void rebond();
        void move();
        void trace();
    protected:
    private:
        float m_x_pos;
        float m_y_pos;
        float m_x_vit;
        float m_y_vit;
        float m_rayon;
        //char* m_img;
};

#endif // BILLE_H
