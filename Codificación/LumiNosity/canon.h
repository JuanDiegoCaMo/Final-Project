#ifndef CANON_H
#define CANON_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>

class canon: public QObject, public QGraphicsPixmapItem
{
public:
    canon(int width, int height);
    void setImg(int type, bool part);
    bool getWhichPart();
    int getPower();
    void setPower(int setPwr);
private:
    QPixmap original, img, base;
    int w,h,power = 0;
    bool whichPart = false;
};

#endif // CANON_H
