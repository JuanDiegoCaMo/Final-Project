#ifndef PROTA_H
#define PROTA_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>

class prota: public QObject, public QGraphicsPixmapItem
{
public:
    prota(int width, int height);
    void setSize(int width, int height);
    void setAnim();
private:
    QPixmap original[8], img;
    int w,h;
};

#endif // PROTA_H
