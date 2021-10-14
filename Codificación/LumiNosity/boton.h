#ifndef BOTON_H
#define BOTON_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>

class boton: public QObject, public QGraphicsPixmapItem
{
public:
    boton();
private:
    QPixmap original;
};

#endif // BOTON_H
