#include "chargers.h"

chargers::chargers(int width, int height)
{
   w = width;
   h = height;
   low.load(":/images/Cargador/charge_1.png");
   charged.load(":/images/Cargador/charge_0.png");
   medium.load(":/images/Cargador/charge_2.png");
   setPixmap(low.scaled(w,h));
}

void chargers::setImg(int type)
{
    if(type==0) setPixmap(low.scaled(w,h));
    else if(type==1) setPixmap(medium.scaled(w,h));
    else if(type==2) setPixmap(charged.scaled(w,h));
    tipo = type;
}

int chargers::getTipo()
{
    return tipo;
}

int chargers::getLastProt()
{
    return lastProt;
}

void chargers::setLastProt(int last)
{
    lastProt = last;
}
