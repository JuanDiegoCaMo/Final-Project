#ifndef CHARGERS_H
#define CHARGERS_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>

class chargers: public QObject, public QGraphicsPixmapItem //Cargador
{
public:
    chargers(int width, int height);
    void setImg(int type);
    int getTipo();
    int getLastProt();
    void setLastProt(int last);
private:
    QPixmap charged, low, medium;
    int w,h, tipo = 0, lastProt = 0;
};

#endif // CHARGERS_H
