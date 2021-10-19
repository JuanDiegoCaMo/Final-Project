#include "ene_sierra.h"

ene_sierra::ene_sierra(int width, int height, int cont)
{
    w = width;
    h = height;
    original.load(":/images/Sierra Circular/sierra.png");
    setSize(w,h,cont);
}

void ene_sierra::setSize(int width, int height, int cont)
{
    img = original.copy(cont*32,0,32,32);
    setPixmap(img.scaled(width,height));
}

void ene_sierra::setAnim()
{
    setSize(w,h,cont);
    if(cont==3) dirAnim = 0;
    else if(cont==0) dirAnim = 1;
    if(dirAnim) cont = cont + 1;
    else cont = cont - 1;
}
