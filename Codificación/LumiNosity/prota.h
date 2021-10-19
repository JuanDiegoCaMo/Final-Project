#ifndef PROTA_H
#define PROTA_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QString>

class prota: public QObject, public QGraphicsPixmapItem
{
public:
    prota(int width, int height, bool type);
    void setSize(int width, int height, bool type,int cont);
    void setAnim(bool numAnim);
    float getScale();
    void setNumScale(float scaleNum);
    int getEnergy();
    void setEnergy(int ener);
private:
    QPixmap original, img;
    int w,h, cont=0, energy = 3;
    float scale = 1;
    bool dirAnim = true;
};

#endif // PROTA_H
