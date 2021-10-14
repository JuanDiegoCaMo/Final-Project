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
private:
    QPixmap original, img;
    int w,h, cont=0;
    bool dirAnim = true;
};

#endif // PROTA_H
