#include "ene_sierra.h"

ene_sierra::ene_sierra(int width, int height)
{
    w = width;
    h = height;
    original.load(":/images/Sierra Circular/sierra.png");
    img = original.copy(0,0,32,32);
    setPixmap(img.scaled(w,h));
}

void ene_sierra::setImg(int type)
{
    img = original.copy(32*type,0,32,32);
    setPixmap(img.scaled(w,h));
}
