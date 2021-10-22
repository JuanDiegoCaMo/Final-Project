#ifndef ENE_SIERRA_H
#define ENE_SIERRA_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>

class ene_sierra: public QObject, public QGraphicsPixmapItem
{
public:
    ene_sierra(int width, int height, int cont);
    void setSize(int width, int height, int cont);
    void setAnim();
    int getTypeMov();
    void setTypeMov(int typeOfMov);
private:
    QPixmap original, img;
    int w,h, cont=0;
    bool dirAnim = true;
    int typeMov = 0;
};

#endif // ENE_SIERRA_H
