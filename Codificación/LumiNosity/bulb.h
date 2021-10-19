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
private:
    QPixmap original, img;
    int w,h;
};

#endif // BULB_H
