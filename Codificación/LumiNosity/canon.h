#ifndef CANON_H
#define CANON_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>

class canon: public QObject, public QGraphicsPixmapItem
{
public:
    canon(int width, int height);
private:
    QPixmap original;
    int w,h;
};

#endif // CANON_H
