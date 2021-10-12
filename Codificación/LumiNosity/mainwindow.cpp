#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    prot1 = new prota(tam,tam);
    prot2 = new prota(tam,tam);

    ui->setupUi(this);
    setupWindow();
    setupMapa();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupWindow()
{
    scene=new QGraphicsScene;
    ui->graphicsView->setGeometry(0,0,tam*ancho+2,tam*alto+2);
    scene->setSceneRect(0,0,tam*ancho,tam*alto);
    ui->graphicsView->setScene(scene);
    setFixedSize(tam*ancho+2,tam*alto+2);
    setWindowTitle("LumiNosity");
    timeMovProta = new QTimer;
    timeMovProta->start(100);

    connect(timeMovProta,SIGNAL(timeout()),this,SLOT(animProta()));
}

void MainWindow::setupMapa()
{
    prot1->setPos(tam*1,tam*1);
    prot2->setPos(tam*(ancho-2),tam*(alto-2));
    scene->addItem(prot1);
    scene->addItem(prot2);
}

void MainWindow::animProta()
{

}

void MainWindow::keyPressEvent(QKeyEvent *key){
    if(key->key() == Qt::Key_W){
        prot1->setY(prot1->y()-(tam/10));
    }
    else if(key->key() == Qt::Key_A){
        prot1->setX(prot1->x()-(tam/10));
    }
    else if(key->key() == Qt::Key_S){
        prot1->setY(prot1->y()+(tam/10));
    }
    else if(key->key() == Qt::Key_D){
        prot1->setX(prot1->x()+(tam/10));
    }
    if(key->key() == Qt::Key_Q){ //Vincular Player 1

    }
    else if(key->key() == Qt::Key_E){ //Interactuar Player 1

    }
    if(key->key() == Qt::Key_I){
        prot2->setY(prot2->y()-(tam/10));
    }
    else if(key->key() == Qt::Key_J){
        prot2->setX(prot2->x()-(tam/10));
    }
    else if(key->key() == Qt::Key_K){
        prot2->setY(prot2->y()+(tam/10));
    }
    else if(key->key() == Qt::Key_L){
        prot2->setX(prot2->x()+(tam/10));
    }
    if(key->key() == Qt::Key_U){ //Vincular Player 2

    }
    else if(key->key() == Qt::Key_O){ //Interactuar Player 2

    }
}

void MainWindow::on_newGame_clicked()
{
    ui->newGame->hide();
    ui->newGame->setEnabled(false);
    ui->loadGame->hide();
    ui->loadGame->setEnabled(false);
    ui->exit->hide();
    ui->exit->setEnabled(false);
}

