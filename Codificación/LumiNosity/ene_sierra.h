#ifndef ENE_SIERRA_H
#define ENE_SIERRA_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>

class ene_sierra: public QObject, public QGraphicsPixmapItem
{
public:
    ene_sierra(int width, int height);
    void setImg(int type);
private:
    QPixmap original, img;
    int w,h;
};

#endif // ENE_SIERRA_H
