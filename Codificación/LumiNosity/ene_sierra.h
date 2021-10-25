#ifndef ENE_SIERRA_H
#define ENE_SIERRA_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>

class ene_sierra: public QObject, public QGraphicsPixmapItem
{
public:
    ene_sierra(int width, int height, int cont);
    void setSize(int width, int height, int cont);
    void setAnim();
    int getTypeMov();
    void setTypeMov(int typeOfMov);
    long int getCenterX();
    long int getCenterY();
    long int getA();
    long int getB();
    long double getVelAng();
    long double getInitAng();
    void setCenterX(long int _X);
    void setCenterY(long int _Y);
    void setA(long int _A);
    void setB(long int _B);
    void setVelAng(long double _W);
    void setInitAng(long double _Ang);
    long long int getCounter();
    void setCounter(long long int counter);
    long double getVelAngMax();
    void setVelAngMax(long double _WMAX);
private:
    QPixmap original, img;
    int w,h, cont=0;
    bool dirAnim = true;
    int typeMov = 0;
    long double velAng = 0, initAng = 0, velAngMax = 0;
    long int a = 1, b = 1, centerX = 0, centerY = 0;
    unsigned long long int n = 0;
};

#endif // ENE_SIERRA_H
