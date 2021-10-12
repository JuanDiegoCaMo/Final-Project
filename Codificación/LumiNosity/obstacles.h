#ifndef OBSTACLES_H
#define OBSTACLES_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>

class obstacles: public QObject, public QGraphicsPixmapItem //Muro, cables y Fondo
{
public:
    obstacles();
};

#endif // OBSTACLES_H
