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
