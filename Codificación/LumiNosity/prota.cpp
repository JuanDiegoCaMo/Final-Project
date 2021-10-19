#include "prota.h"

prota::prota(int width, int height, bool type)
{
    w = width;
    h = height;
    original.load(":/images/Jugadores/Per_0.png");
    setSize(w,h,type,cont);
}

void prota::setSize(int width, int height, bool type, int cont)
{
    img = original.copy((4*type+cont)*32,0,32,33);
    setPixmap(img.scaled(width,height));
}

void prota::setAnim(bool numAnim)
{
    setSize(w,h,numAnim,cont);
    if(cont==3) dirAnim = 0;
    else if(cont==0) dirAnim = 1;
    if(dirAnim) cont = cont + 1;
    else cont = cont - 1;
}

float prota::getScale()
{
    return scale;
}

void prota::setNumScale(float scaleNum)
{
    scale = scaleNum;
}

int prota::getEnergy()
{
    return energy;
}

void prota::setEnergy(int ener)
{
    energy = ener;
}
