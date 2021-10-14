#ifndef ENE_RESISTOR_H
#define ENE_RESISTOR_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>

class ene_resistor: public QObject, public QGraphicsPixmapItem
{
public:
    ene_resistor();
    bool getIsColliding();
    void setIsColliding(bool setColl);
    bool getHasButton();
private:
    QPixmap original;
    int w,h, numButton = 0;
    bool isColliding = false, hasButton = false;
};

#endif // ENE_RESISTOR_H
