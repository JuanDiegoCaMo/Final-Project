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

int ene_sierra::getTypeMov()
{
    return typeMov;
}

void ene_sierra::setTypeMov(int typeOfMov)
{
    typeMov = typeOfMov;
}

long int ene_sierra::getCenterX()
{
    return centerX;
}

long int ene_sierra::getCenterY()
{
    return centerY;
}

long ene_sierra::getA()
{
    return a;
}

long ene_sierra::getB()
{
    return b;
}

long double ene_sierra::getVelAng()
{
    return velAng;
}

long double ene_sierra::getInitAng()
{
    return initAng;
}

void ene_sierra::setCenterX(long int _X)
{
    centerX = _X;
}

void ene_sierra::setCenterY(long int _Y)
{
    centerY = _Y;
}

void ene_sierra::setA(long _A)
{
    a = _A;
}

void ene_sierra::setB(long _B)
{
    b = _B;
}

void ene_sierra::setVelAng(long double _W)
{
    velAng = _W;
}

void ene_sierra::setInitAng(long double _Ang)
{
    initAng = _Ang;
}

long long ene_sierra::getCounter()
{
    return n;
}

void ene_sierra::setCounter(long long counter)
{
    n = counter;
}
