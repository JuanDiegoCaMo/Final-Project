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
private:
    QPixmap original, img, base;
    int w,h;
};

#endif // CANON_H
