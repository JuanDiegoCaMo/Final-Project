#include "movilplat.h"

movilPlat::movilPlat(int width, int height)
{
    w = width;
    h = height;
    original.load(":/images/PlatMovil/platmov_0.png");
    img = original.copy(0,0,32,32);
    setPixmap(img.scaled(w,h));
}

void movilPlat::setImg(int type)
{
    img = original.copy(32*type,0,32,32);
    setPixmap(img.scaled(w,h));
}
