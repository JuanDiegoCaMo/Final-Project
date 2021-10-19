#include "canon.h"

canon::canon(int width, int height)
{
    w = width;
    h = height;
    original.load(":/images/Canon/tube.png");
    base.load(":/images/Canon/base.png");
    img = original.copy(0,0,55,32);
    setPixmap(img.scaled(w,h));
}

void canon::setImg(int type, bool part)
{
    if(part){
        img = original.copy(55*type,0,55,32);
        setPixmap(img.scaled(w,5*h/8));
    }
    else{
        if(type%2==0) img = base.copy(38*0+type,0,38,42);
        else    img = base.copy(38*1+type,0,38,42);
        setPixmap(img.scaled(w,h));
    }
}
