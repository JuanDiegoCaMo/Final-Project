#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QString>
#include <QMessageBox>
#include <QFontDatabase>
#include <QTimer>
#include <QImage>
#include <QKeyEvent>
#include <QtMath>
#include "math.h"
#include "boton.h"
#include "bulb.h"
#include "canon.h"
#include "canonball.h"
#include "chargers.h"
#include "ene_resistor.h"
#include "ene_sierra.h"
#include "movilplat.h"
#include "obstacles.h"
#include "prota.h"
#include "Metodo_2.h"

#define ancho 33 //max 1350
#define alto 17 //max 690
#define tam 40

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void keyPressEvent(QKeyEvent *key);
    ~MainWindow();
    void setupWindow();
    void setupMapa();
    void setupObjectslvl1();
    void sceneScale1();
    void nextLvl();
    bool evalEnergy(bool isProt1, int modify);
    bool codeTxt(int semilla,string n_archivo, bool first);
    string decodeTxt(int semilla, string n_archivo);
public slots:
    void animProta();
    void simul();

private slots:
    void on_newGame_clicked();

private:
    Ui::MainWindow *ui;
    prota *prot1, *prot2;
    obstacles **mapa, **energy;
    boton **button;
    bulb *bombilla;
    movilPlat **plat1;
    ene_sierra **sierra;
    ene_resistor **resistor;
    chargers **cargador;
    canonBall *ball, *ball2;
    canon **canion;
    QGraphicsScene *scene;
    QByteArray geoCan1, geoCan2;
    QTimer *timeMovProta, *timeSimuls;
    short int lvl1[alto][ancho];
    int actualLvl = 1;
    int contObs = 0, contCanons = 0, contPlats = 0, contSierras = 0, contResis = 0, contButts = 0, lives = 3, T = 50, movY = 0, movY2 = 0;
    double scaleFactor = 0.625;
    bool canonKeys1 = false, canonKeys2 = false, bulb1 = false, bulb2 = false;
};
#endif // MAINWINDOW_H
