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
    void setCountToChange(int count);
    int getCountToChange();
    int getAllowMov();
    void setAllowMov(int allow);
    int getNumBut();
    void setNumBut(int but);
    bool getTrigger();
    void setTrigger(bool trig);
    qreal getOriginX();
    qreal getOriginY();
    void setOriginY(qreal _y);
    void setOriginX(qreal _x);
private:
    QPixmap original, img;
    int w,h, tipo = 0, dir = 1, countToChange = 0;
    int allowMov = 1, numBut = 0;
    bool trigger = false;
    qreal originX = 0, originY = 0;
};

#endif // MOVILPLAT_H
