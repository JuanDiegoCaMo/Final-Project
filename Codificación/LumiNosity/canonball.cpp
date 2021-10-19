#include "canonball.h"

canonBall::canonBall(int width, int height)
{
    original.load(":/images/BolaCanon/ball_0.png");
    w = width;
    h = height;
    setPixmap(original.scaled(w,h));
}
