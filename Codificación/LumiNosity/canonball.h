#ifndef CANONBALL_H
#define CANONBALL_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>

class canonBall: public QObject, public QGraphicsPixmapItem
{
public:
    canonBall(int width, int height);
    void setAnim();
private:
    QPixmap original;
    int w, h, cont = 0;
};

#endif // CANONBALL_H
