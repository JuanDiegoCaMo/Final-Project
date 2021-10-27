#ifndef BOTON_H
#define BOTON_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>

class boton: public QObject, public QGraphicsPixmapItem
{
public:
    boton(int width, int height);
    void setImg(int type);
    void setNumButton(int numButt);
    int getNumButton();
    void setStartAnim(bool anim);
    bool getStartAnim();
    void setAnim();
private:
    QPixmap original,img;
    int w,h, numButton = 0, tipo = 0, cont = 0;
    bool startAnim = false;
};

#endif // BOTON_H
