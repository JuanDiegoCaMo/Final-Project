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
    int getTipo();
    int getDir();
    void setDir(int direction);
private:
    QPixmap original, img;
    int w,h, tipo = 0, dir = 1;
};

#endif // MOVILPLAT_H
