#include "ene_resistor.h"

ene_resistor::ene_resistor(int width, int height)
{
    w = width;
    h = height;
    original.load(":/images/Resistor Circular/resistor_0.png");
    setPixmap(original.scaled(w,h));
}

bool ene_resistor::getHasButton()
{
    return hasButton;
}

void ene_resistor::setHasButton(bool setButt, int numOfButt)
{
    hasButton = setButt;
    numButton = numOfButt;
}

int ene_resistor::getNumButton()
{
    return numButton;
}

void ene_resistor::replace(int type)
{
    cables.load(":/images/Obstaculos/obs.png");
    img = cables.copy(32*type,0,32,32);
    setPixmap(img.scaled(w,h));
}
