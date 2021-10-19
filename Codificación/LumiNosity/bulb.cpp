#include "bulb.h"

bulb::bulb(int width, int height)
{
    w = width;
    h = height;
    original.load(":/images/Bombilla/bulb.png");
    img = original.copy(0,0,14,23);
    setPixmap(img.scaled(w,h));
}

void bulb::setImg(int type)
{
    img = original.copy(14*type,0,14,23);
    setPixmap(img.scaled(w,h));
}
