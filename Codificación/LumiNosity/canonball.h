#ifndef CANONBALL_H
#define CANONBALL_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>

class canonBall: public QObject, public QGraphicsPixmapItem
{
public:
    canonBall(int width, int height);
    void setAnim();
    int getHeight();
    bool getActivate();
    void setActivate(bool activ);
    unsigned long long getN();
    void setN(unsigned long long int newN);
    int getX0();
    void setX0(int _X0);
    int getY0();
    void setY0(int _Y0);
    double getVx0();
    void setVx0(double _Vx0);
    double getVy0();
    void setVy0(double _Vy0);
private:
    QPixmap original, img;
    int w, h, cont = 0, x0 = 0, y0 = 0;
    double vx0 = 0, vy0 = 0;
    unsigned long long n = 0;
    bool activate = false;
};

#endif // CANONBALL_H
