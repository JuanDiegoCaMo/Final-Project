#include "bulb.h"

bulb::bulb(int width, int height)
{
    w = width;
    h = height;
    original.load(":/images/Bombilla/bulb.png");
    img = original.copy(0,0,32,37);
    setPixmap(img.scaled(w,h));
}

void bulb::setImg(int type)
{
    img = original.copy(32*type,0,32,37);
    setPixmap(img.scaled(w,h));
}
