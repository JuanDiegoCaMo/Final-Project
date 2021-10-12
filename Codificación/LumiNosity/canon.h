#ifndef CANON_H
#define CANON_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>

class canon: public QObject, public QGraphicsPixmapItem
{
public:
    canon();
};

#endif // CANON_H
