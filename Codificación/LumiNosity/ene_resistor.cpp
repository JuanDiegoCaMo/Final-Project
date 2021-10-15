#include "ene_resistor.h"

ene_resistor::ene_resistor(int width, int height)
{
    w = width;
    h = height;
    original.load(":/images/Resistor Circular/resistor_0.png");
    setPixmap(original.scaled(w,h));
}

bool ene_resistor::getIsColliding()
{
    return isColliding;
}

void ene_resistor::setIsColliding(bool setColl)
{
    isColliding = setColl;
}

bool ene_resistor::getHasButton()
{
    return hasButton;
}
