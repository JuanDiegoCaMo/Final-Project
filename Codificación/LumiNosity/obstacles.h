#ifndef OBSTACLES_H
#define OBSTACLES_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>

class obstacles: public QObject, public QGraphicsPixmapItem //Muro, Cables y Fondo
{
public:
    obstacles(int width, int height);
    void setImg(int type);
private:
    QPixmap original, img;
    int w, h;
};

#endif // OBSTACLES_H
