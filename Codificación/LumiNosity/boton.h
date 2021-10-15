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
private:
    QPixmap original,img;
    int w,h;
};

#endif // BOTON_H
