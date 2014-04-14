#ifndef OBSTACLE_H
#define OBSTACLE_H

using namespace std;

class obstacle
{
    public:
        obstacle(/*std::string imgPath*/);
        virtual ~obstacle();
        //bille(const bille& other);
        int get_x_pos() const;
        int get_y_pos() const;
        void chg_x_pos(int nXpos);
        void chg_y_pos(int nYpos);
    protected:
        int m_x_pos;
        int m_y_pos;
    private:

        //char* m_img;
};

#endif // BILLE_H
