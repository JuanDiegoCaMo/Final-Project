#ifndef CHARGERS_H
#define CHARGERS_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>

class chargers: public QObject, public QGraphicsPixmapItem //Cargador
{
public:
    chargers();
};

#endif // CHARGERS_H
