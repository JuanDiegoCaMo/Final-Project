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
