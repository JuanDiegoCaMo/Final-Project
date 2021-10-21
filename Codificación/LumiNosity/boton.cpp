#include "boton.h"

boton::boton(int width, int height)
{
    w = width;
    h = height;
    original.load(":/images/Boton/button_0.png");
    img = original.copy(0,0,32,29);
    setPixmap(img.scaled(w,h));
}

void boton::setImg(int type)
{
    img = original.copy(32*type,0,32,29);
    setPixmap(img.scaled(w,h));
    tipo = type;
}

void boton::setNumButton(int numButt)
{
    numButton = numButt;
}

int boton::getNumButton()
{
    return numButton;
}

void boton::setStartAnim(bool anim)
{
    startAnim = anim;
}

bool boton::getStartAnim()
{
    return startAnim;
}

void boton::setAnim()
{
    if(cont<4){
        img = original.copy(32*(tipo+cont),0,32,29);
        setPixmap(img.scaled(w,h));
        cont++;
    }
    else setStartAnim(false);
}
