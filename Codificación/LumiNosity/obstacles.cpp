#include "obstacles.h"

obstacles::obstacles(int width, int height)
{
    w = width;
    h = height;
    original.load(":/images/Obstaculos/obs.png");
    img = original.copy(0,0,32,32);
    energy.load(":/images/Obstaculos/obs_energy.png");
    setPixmap(img.scaled(w,h));
}

void obstacles::setImg(int type)
{
    img = original.copy(32*type,0,32,32);
    setPixmap(img.scaled(w,h));
    tipo = type;
}

void obstacles::setImgEnergy()
{
    setPixmap(energy.scaled(w,h));
}

int obstacles::getTipo()
{
    return tipo;
}
