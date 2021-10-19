#ifndef ENE_RESISTOR_H
#define ENE_RESISTOR_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>

class ene_resistor: public QObject, public QGraphicsPixmapItem
{
public:
    ene_resistor(int width, int height);
    bool getHasButton();
    void setHasButton(bool setButt, int numOfButt);
private:
    QPixmap original;
    int w,h, numButton = 0;
    bool hasButton = false;
};

#endif // ENE_RESISTOR_H
