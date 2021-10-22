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
    if(type == 2) tipo = 1;
    else if(type == 0) tipo = 0;
}

int movilPlat::getTipo()
{
    return tipo;
}

int movilPlat::getDir()
{
    return dir;
}

void movilPlat::setDir(int direction)
{
    dir = direction;
}

void movilPlat::setCountToChange(int count)
{
    countToChange = count;
}

int movilPlat::getCountToChange()
{
    return countToChange;
}

int movilPlat::getAllowMov()
{
    return allowMov;
}

void movilPlat::setAllowMov(int allow)
{
    allowMov = allow;
}
