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
    void setImgAlternate(int type);
    int getTipo();
private:
    QPixmap original, img, energy, lives;
    int w, h, tipo = -1;
};

#endif // OBSTACLES_H
