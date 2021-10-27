#include "canonball.h"

canonBall::canonBall(int width, int height)
{
    original.load(":/images/BolaCanon/ball_0.png");
    w = width/2;
    h = height/2;
    setPixmap(original.scaled(w,h));
}

void canonBall::setAnim()
{

}

int canonBall::getHeight()
{
    return h;
}

bool canonBall::getActivate()
{
    return activate;
}

void canonBall::setActivate(bool activ)
{
    activate = activ;
}

unsigned long long canonBall::getN()
{
    return n;
}

void canonBall::setN(unsigned long long newN)
{
    n = newN;
}

int canonBall::getX0()
{
    return x0;
}

void canonBall::setX0(int _X0)
{
    x0 = _X0;
}

int canonBall::getY0()
{
    return y0;
}

void canonBall::setY0(int _Y0)
{
    y0 = _Y0;
}

double canonBall::getVx0()
{
    return vx0;
}

void canonBall::setVx0(double _Vx0)
{
    vx0 = _Vx0;
}

double canonBall::getVy0()
{
    return vy0;
}

void canonBall::setVy0(double _Vy0)
{
    vy0 = _Vy0;
}
