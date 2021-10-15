#ifndef MOVILPLAT_H
#define MOVILPLAT_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>

class movilPlat: public QObject, public QGraphicsPixmapItem
{
public:
    movilPlat(int width, int height);
    void setImg(int type);
private:
    QPixmap original, img;
    int w,h;
};

#endif // MOVILPLAT_H
