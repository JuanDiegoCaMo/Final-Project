#ifndef ENE_RESISTOR_H
#define ENE_RESISTOR_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>

class ene_resistor: public QObject, public QGraphicsPixmapItem
{
public:
    ene_resistor();
};

#endif // ENE_RESISTOR_H
