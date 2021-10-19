#include "canon.h"

canon::canon(int width, int height)
{
    w = width;
    h = height;
    original.load(":/images/Cargador/charge_0.png");
    setPixmap(original.scaled(w,h));
}
