#ifndef BULB_H
#define BULB_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>

class bulb: public QObject, public QGraphicsPixmapItem
{
public:
    bulb(int width, int height);
    void setImg(int type);
    int getTipo();
private:
    QPixmap original, img;
    int w,h, tipo = 0;
};

#endif // BULB_H
