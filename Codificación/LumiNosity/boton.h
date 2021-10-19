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
private:
    QPixmap original,img;
    int w,h, numButton = 0;
};

#endif // BOTON_H
