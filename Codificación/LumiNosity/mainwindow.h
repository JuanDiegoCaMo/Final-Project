#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QString>
#include <QFontDatabase>
#include <QTimer>
#include <QKeyEvent>
#include "canon.h"
#include "canonball.h"
#include "chargers.h"
#include "ene_resistor.h"
#include "ene_sierra.h"
#include "movilplat.h"
#include "obstacles.h"
#include "prota.h"

#define ancho 45
#define alto 23
#define tam 30

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
public slots:
    void animProta();

private slots:
    void on_newGame_clicked();

private:
    Ui::MainWindow *ui;
    prota *prot1, *prot2;
    obstacles *mapa;
    movilPlat *plat1;
    ene_sierra *sierra;
    ene_resistor *resistor;
    chargers *cargador;
    canonBall *ball;
    canon *canon;
    QGraphicsScene *scene;
    QTimer *timeMovProta;
};
#endif // MAINWINDOW_H
