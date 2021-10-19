#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ball = new canonBall(tam,tam);
    bombilla = new bulb(tam,tam);

    ui->setupUi(this);
    timeMovProta = new QTimer;
    timeMovProta->start(75);

    connect(timeMovProta,SIGNAL(timeout()),this,SLOT(animProta()));
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
    ui->graphicsView->setBackgroundBrush(QBrush(QImage(":/images/Obstaculos/obs_1.png")));
    setFixedSize(tam*ancho+2,tam*alto+2);
    setWindowTitle("LumiNosity");

}

void MainWindow::setupMapa()
{
    setupObjectslvl1();
    prot1 = new prota(tam,tam,0);
    prot2 = new prota(tam,tam,1);
    prot1->setPos(tam*1,tam*1);
    prot2->setPos(tam*(ancho-2),tam*(alto-2));
    ball->setPos(tam*2,tam*2);
    scene->addItem(prot1);
    scene->addItem(prot2);
    scene->addItem(ball);
}

void MainWindow::setupObjectslvl1()
{
    /*static unsigned char lvl1[alto][ancho]={ //Revisar octales, tipo short[33]
        {00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00},
        {00,15,03,99,03,03,03,11,03,99,03,03,14,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,00},
        {00,02,01,01,01,01,01,02,01,01,01,01,99,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,00},
        {00,99,01,01,01,01,01,12,99,03,03,003,9,03,96,03,03,03,03,03,03,98,03,03,03,03,14,01,01,01,01,01,00},
        {00,02,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,96,01,01,01,01,01,00},
        {000,8,03,14,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,01,01,001,8,03,03,03,14,01,00},
        {00,02,01,02,00,01,01,01,01,01,01,01,01,97,01,01,01,01,01,01,01,01,00,01,01,01,02,01,01,01,02,01,00},
        {00,99,01,02,00,01,01,01,01,01,01,01,01,97,01,01,01,01,01,01,01,01,00,01,01,01,02,01,01,01,99,01,00},
        {00,02,01,02,00,01,01,01,01,01,01,97,01,97,01,97,01,01,01,01,01,01,00,01,01,01,99,01,01,01,12,14,00},
        {00,99,01,02,01,01,01,01,01,01,01,01,97,01,97,01,01,01,01,01,01,01,01,15,03,003,9,03,14,01,01,02,00},
        {00,12,99,10,01,01,01,01,01,01,01,01,01,97,01,01,01,01,01,01,01,01,01,99,01,01,01,01,12,99,03,10,00},
        {00,01,01,02,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,001,8,03,14,01,01,01,01,01,02,00},
        {00,01,01,12,95,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,95,10,01,02,01,01,01,01,01,02,00},
        {00,01,01,01,00,01,01,01,94,00,01,01,01,01,01,01,01,00,94,01,01,01,00,02,001,8,99,14,01,01,01,99,00},
        {00,01,01,01,00,01,01,01,01,00,01,50,50,50,50,50,01,00,01,01,01,01,00,12,99,10,01,99,01,01,01,02,00},
        {00,01,01,01,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,01,01,12,003,9,03,99,03,13,00},
        {00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00}
    };*/
    string info1, objslvl1 = "lvl1.dat", subinfo1;
    int semilla = 7;
    bool write = true;
    contObs = 0, contCanons = 0, contPlats = 0, contSierras = 0, contResis = 0, contButts = 0;
    info1 = decodeTxt(semilla,objslvl1);
    if(info1[0] == ',' && info1[1] == '0' && info1[2] == '0') write = false;
    codeTxt(semilla,objslvl1, write);
    info1 = decodeTxt(semilla,objslvl1);
    for(int i=0; i<int(info1.length()); i++){
        if(info1[i] == ','){
            subinfo1.push_back(info1[i+1]);
            subinfo1.push_back(info1[i+2]);
            int mult = 10, data = 0;
            for(int ind = 0; ind<int(subinfo1.length()); ind++){
                data += ((subinfo1[ind]-48)*mult);
                mult /= 10;
            }
            if(data<=16){
                contObs++;
            }
            else if(data==99 || data==96){
                contResis++;
            }
            else if(data>=50 && data<=54){
                contButts++;
            }
            else if(data==97){
                contSierras++;
            }
            else if(data==95 || data==92){
                contCanons+=2;
            }
            else if(data==94 || data==93){
                contPlats++;
            }
            subinfo1.clear();
        }
    }
    /*for(int fil=0; fil<alto; fil++){
        for(int col=0; col<ancho; col++){
            if(int(lvl1[fil][col])<=16){
                contObs++;
            }
            else if(int(lvl1[fil][col])==99 || int(lvl1[fil][col])==96){
                contResis++;
            }
            else if(int(lvl1[fil][col])==50){
                contButts++;
            }
            else if(int(lvl1[fil][col])==97){
                contSierras++;
            }
            else if(int(lvl1[fil][col])==95){
                contCanons++;
            }
            else if(int(lvl1[fil][col])==94){
                contPlats++;
            }
        }
    }*/
    mapa = new obstacles*[contObs];
    for(int i=0; i<contObs; i++)    mapa[i] = new obstacles(tam,tam);
    canion = new canon*[contCanons];
    for(int i=0; i<contCanons; i++)    canion[i] = new canon(tam,tam);
    resistor = new ene_resistor*[contResis];
    for(int i=0; i<contResis; i++)    resistor[i] = new ene_resistor(tam,tam);
    sierra = new ene_sierra*[contSierras];
    for(int i=0; i<contSierras; i++)    sierra[i] = new ene_sierra(tam,tam,0);
    button = new boton*[contButts];
    for(int i=0; i<contButts; i++)    button[i] = new boton(tam,tam);
    plat1 = new movilPlat*[contPlats];
    for(int i=0; i<contPlats; i++)    plat1[i] = new movilPlat(tam,tam);

    contPlats = 0, contButts = 0, contSierras = 0, contResis = 0, contCanons = 0, contObs = 0;
    int anch = 0, alt = 0;
    for(int i=0; i<int(info1.length()); i++){
        if(info1[i] == ','){
            subinfo1.push_back(info1[i+1]);
            subinfo1.push_back(info1[i+2]);
            int mult = 10, data = 0;
            int canWalk = 0;
            for(int ind = 0; ind<int(subinfo1.length()); ind++){
                data += ((subinfo1[ind]-48)*mult);
                mult /= 10;
            }
            if(data<=16){
                if(data<=16 && data>= 2) canWalk = 1;
                mapa[contObs]->setImg(data);
                mapa[contObs]->setPos(anch*tam,alt*tam);
                scene->addItem(mapa[contObs]);
                contObs++;
            }
            else if(data==99 || data==96){
                canWalk = 2;
                resistor[contResis]->setPos(anch*tam,alt*tam);
                if(data == 96) resistor[contResis]->setHasButton(true,1);
                scene->addItem(resistor[contResis]);
                contResis++;
            }
            else if(data>=50 && data <= 54){
                button[contButts]->setImg((data-50)*4);
                button[contButts]->setPos(anch*tam,alt*tam);
                button[contButts]->setNumButton((data-49));
                scene->addItem(button[contButts]);
                contButts++;
            }
            else if(data==97){
                sierra[contSierras]->setPos(anch*tam,alt*tam);
                scene->addItem(sierra[contSierras]);
                contSierras++;
            }
            else if(data==95 || data==92){
                canWalk = -1;
                canion[contCanons]->setPos(anch*tam,alt*tam);
                canion[contCanons]->setImg(0,false);
                canion[contCanons+1]->setPos(anch*tam,alt*tam+tam/10);
                if(data==95) canion[contCanons+1]->setImg(0,true);
                else    canion[contCanons+1]->setImg(2,true);
                scene->addItem(canion[contCanons]);
                scene->addItem(canion[contCanons+1]);
                contCanons+=2;
            }
            else if(data<=94 && data>= 93){
                plat1[contPlats]->setImg((data-93)*2);
                plat1[contPlats]->setPos(anch*tam,alt*tam);
                scene->addItem(plat1[contPlats]);
                contPlats++;
            }
            else if(data==98){
                bombilla->setImg(0);
                bombilla->setPos(anch*tam,alt*tam);
                scene->addItem(bombilla);
            }
            subinfo1.clear();
            lvl1[alt][anch] = canWalk;
            anch+=1;
        }
        if(info1[i] == ';'){
            alt+=1;
            anch=0;
        }
    }
}

bool MainWindow::evalEnergy(bool isProt1, int modify)
{
    if(isProt1){
        prot1->setEnergy(prot1->getEnergy()+modify);
    }
    else{
        prot2->setEnergy(prot2->getEnergy()+modify);
    }
    if(prot2->getEnergy() == 0 || prot1->getEnergy() == 0){
        lives = lives+modify;
        prot1->setNumScale(1.00);
        prot1->setScale(prot1->getScale());
        prot1->setPos(1*tam,1*tam);
        prot2->setNumScale(1.00);
        prot2->setScale(prot2->getScale());
        prot2->setPos(tam*(ancho-2),tam*(alto-2));
        prot1->setEnergy(3);
        prot2->setEnergy(3);
        delete []mapa;
        delete []button;
        delete []plat1;
        delete []sierra;
        delete []resistor;
        delete []canion;
        setupMapa();
        if(lives == 0){
                switch(QMessageBox::question(
                    this,
                    tr("LumiNosity"),
                    tr("GAME OVER.\n"
                       "Reiniciar?") ,
                QMessageBox::Yes | QMessageBox::No))
                {
                case QMessageBox::Yes:
                        lives = 3;
                        break;
                case QMessageBox::No:
                    this->close();
                    break;
                }
        }
        return true;
    }
    return false;
}

bool MainWindow::codeTxt(int semilla, string n_archivo, bool first)
{
    bool result=true;
    string texto,binario;
    try {
        texto=leer(n_archivo,true);
        binario=text2bin(texto);
        binario=reglas_codifica(binario,semilla,true);
        texto=bin2text(binario);
        if(first) escribir(texto,n_archivo,false);
    }  catch (...) {
        result=false;
    }
    return result;
}

string MainWindow::decodeTxt(int semilla, string n_archivo)
{
    bool result=true;
    string texto,binario;
    try {
        texto=leer(n_archivo,false);
        binario=text2bin(texto);
        binario=reglas_codifica(binario,semilla,false);
        texto=bin2text(binario);
    }  catch (...) {
        result=false;
    }
    if(result==false) return string("");
    else return texto;
}


void MainWindow::animProta()
{
    prot1->setAnim(0);
    prot2->setAnim(1);
    for(int i=0; i<contSierras; i++) sierra[i]->setAnim();
}

void MainWindow::keyPressEvent(QKeyEvent *key){
    short int mov = 1;
    bool disableMov = false;
    if(key->key() == Qt::Key_Q &&(lvl1[(int(prot1->y())+tam)/tam][int(prot1->x())/tam] == -1 || lvl1[(int(prot1->y())-tam)/tam][int(prot1->x())/tam] == -1 || lvl1[int(prot1->y())/tam][(int(prot1->x())+tam)/tam] == -1 || lvl1[int(prot1->y())/tam][(int(prot1->x())-tam)/tam] == -1)){ //Vincular Player 1
        prot1->setVisible(!prot1->isVisible());
    }
    else if(key->key() == Qt::Key_E){ //Interactuar Player 1

    }
    else if(key->key() == Qt::Key_U &&(lvl1[(int(prot2->y())+tam)/tam][int(prot2->x())/tam] == -1 || lvl1[(int(prot2->y())-tam)/tam][int(prot2->x())/tam] == -1 || lvl1[int(prot2->y())/tam][(int(prot2->x())+tam)/tam] == -1 || lvl1[int(prot2->y())/tam][(int(prot2->x())-tam)/tam] == -1)){ //Vincular Player 2
        prot2->setVisible(!prot2->isVisible());
    }
    else if(key->key() == Qt::Key_O){ //Interactuar Player 2

    }
    if(!prot1->isVisible() && !prot2->isVisible()){
        ui->graphicsView->setSceneRect(tam*4,tam*5,tam*19,tam*11);
        disableMov = true;
        scaleFactor = 1.6;
        ui->graphicsView->scale(scaleFactor,scaleFactor);
    }
    else{
        if(scaleFactor == 1.6) {
            scaleFactor = 0.625;
            ui->graphicsView->scale(scaleFactor,scaleFactor);
            ui->graphicsView->setSceneRect(0,0,tam*ancho,tam*alto);
        }
    }
    if(key->key() == Qt::Key_W && lvl1[(int(prot1->y())-tam)/tam][int(prot1->x())/tam] > 0){
        if(lvl1[(int(prot1->y())-tam)/tam][int(prot1->x())/tam] == 2){
            prot1->setNumScale(4*prot1->getScale()/5);
            prot1->setScale(prot1->getScale());
            lvl1[(int(prot1->y())-tam)/tam][int(prot1->x())/tam] = 3;
            disableMov = evalEnergy(true,-1);
            mov = 2;
        }
        else if(lvl1[(int(prot1->y())-tam)/tam][int(prot1->x())/tam] == 3){
            prot1->setNumScale(5*prot1->getScale()/4);
            prot1->setScale(prot1->getScale());
            lvl1[(int(prot1->y())-tam)/tam][int(prot1->x())/tam] = 2;
            evalEnergy(true,1);
            mov = 2;
        }
        if(!disableMov) prot1->setY(prot1->y()-(tam*mov));
    }
    else if(key->key() == Qt::Key_A && lvl1[int(prot1->y())/tam][(int(prot1->x())-tam)/tam] > 0){
        if(lvl1[int(prot1->y())/tam][(int(prot1->x())-tam)/tam] == 2){
            prot1->setNumScale(4*prot1->getScale()/5);
            prot1->setScale(prot1->getScale());
            lvl1[int(prot1->y())/tam][(int(prot1->x())-tam)/tam] = 3;
            disableMov = evalEnergy(true,-1);
            mov = 2;
        }
        else if(lvl1[int(prot1->y())/tam][(int(prot1->x())-tam)/tam] == 3){
            prot1->setNumScale(5*prot1->getScale()/4);
            prot1->setScale(prot1->getScale());
            lvl1[int(prot1->y())/tam][(int(prot1->x())-tam)/tam] = 2;
            evalEnergy(true,1);
            mov = 2;
        }
        if(!disableMov) prot1->setX(prot1->x()-(tam*mov));
    }
    else if(key->key() == Qt::Key_S && lvl1[(int(prot1->y())+tam)/tam][int(prot1->x())/tam] > 0){
        if(lvl1[(int(prot1->y())+tam)/tam][int(prot1->x())/tam] == 2){
            prot1->setNumScale(4*prot1->getScale()/5);
            prot1->setScale(prot1->getScale());
            lvl1[(int(prot1->y())+tam)/tam][int(prot1->x())/tam] = 3;
            disableMov = evalEnergy(true,-1);
            mov = 2;
        }
        else if(lvl1[(int(prot1->y())+tam)/tam][int(prot1->x())/tam] == 3){
            prot1->setNumScale(5*prot1->getScale()/4);
            prot1->setScale(prot1->getScale());
            lvl1[(int(prot1->y())+tam)/tam][int(prot1->x())/tam] = 2;
            evalEnergy(true,1);
            mov = 2;
        }
        if(!disableMov) prot1->setY(prot1->y()+(tam*mov));
    }
    else if(key->key() == Qt::Key_D && lvl1[int(prot1->y())/tam][(int(prot1->x())+tam)/tam] > 0){
        if(lvl1[int(prot1->y())/tam][(int(prot1->x())+tam)/tam] == 2){
            prot1->setNumScale(4*prot1->getScale()/5);
            prot1->setScale(prot1->getScale());
            lvl1[int(prot1->y())/tam][(int(prot1->x())+tam)/tam] = 3;
            disableMov = evalEnergy(true,-1);
            mov = 2;
        }
        else if(lvl1[int(prot1->y())/tam][(int(prot1->x())+tam)/tam] == 3){
            prot1->setNumScale(5*prot1->getScale()/4);
            prot1->setScale(prot1->getScale());
            lvl1[int(prot1->y())/tam][(int(prot1->x())+tam)/tam] = 2;
            evalEnergy(true,1);
            mov = 2;
        }
        if(!disableMov) prot1->setX(prot1->x()+(tam*mov));
    }
    if(key->key() == Qt::Key_I && lvl1[(int(prot2->y())-tam)/tam][int(prot2->x())/tam] > 0){
        if(lvl1[(int(prot2->y())-tam)/tam][int(prot2->x())/tam] == 2){
            prot2->setNumScale(4*prot2->getScale()/5);
            prot2->setScale(prot2->getScale());
            lvl1[(int(prot2->y())-tam)/tam][int(prot2->x())/tam] = 3;
            disableMov = evalEnergy(false,-1);
            mov = 2;
        }
        else if(lvl1[(int(prot2->y())-tam)/tam][int(prot2->x())/tam] == 3){
            prot2->setNumScale(5*prot2->getScale()/4);
            prot2->setScale(prot2->getScale());
            lvl1[(int(prot2->y())-tam)/tam][int(prot2->x())/tam] = 2;
            evalEnergy(false,1);
            mov = 2;
        }
        if(!disableMov) prot2->setY(prot2->y()-(tam*mov));
    }
    else if(key->key() == Qt::Key_J && lvl1[int(prot2->y())/tam][(int(prot2->x())-tam)/tam] > 0){
        if(lvl1[int(prot2->y())/tam][(int(prot2->x())-tam)/tam] == 2){
            prot2->setNumScale(4*prot2->getScale()/5);
            prot2->setScale(prot2->getScale());
            lvl1[int(prot2->y())/tam][(int(prot2->x())-tam)/tam] = 3;
            disableMov = evalEnergy(false,-1);
            mov = 2;
        }
        else if(lvl1[int(prot2->y())/tam][(int(prot2->x())-tam)/tam] == 3){
            prot2->setNumScale(5*prot2->getScale()/4);
            prot2->setScale(prot2->getScale());
            lvl1[int(prot2->y())/tam][(int(prot2->x())-tam)/tam] = 2;
            evalEnergy(false,1);
            mov = 2;
        }
        if(!disableMov) prot2->setX(prot2->x()-(tam*mov));
    }
    else if(key->key() == Qt::Key_K && lvl1[(int(prot2->y())+tam)/tam][int(prot2->x())/tam] > 0){
        if(lvl1[(int(prot2->y())+tam)/tam][int(prot2->x())/tam] == 2){
            prot2->setNumScale(4*prot2->getScale()/5);
            prot2->setScale(prot2->getScale());
            lvl1[(int(prot2->y())+tam)/tam][int(prot2->x())/tam] = 3;
            disableMov = evalEnergy(false,-1);
            mov = 2;
        }
        else if(lvl1[(int(prot2->y())+tam)/tam][int(prot2->x())/tam] == 3){
            prot2->setNumScale(5*prot2->getScale()/4);
            prot2->setScale(prot2->getScale());
            lvl1[(int(prot2->y())+tam)/tam][int(prot2->x())/tam] = 2;
            evalEnergy(false,1);
            mov = 2;
        }
        if(!disableMov) prot2->setY(prot2->y()+(tam*mov));
    }
    else if(key->key() == Qt::Key_L && lvl1[int(prot2->y())/tam][(int(prot2->x())+tam)/tam] > 0){
        if(lvl1[int(prot2->y())/tam][(int(prot2->x())+tam)/tam] == 2){
            prot2->setNumScale(4*prot2->getScale()/5);
            prot2->setScale(prot2->getScale());
            lvl1[int(prot2->y())/tam][(int(prot2->x())+tam)/tam] = 3;
            disableMov = evalEnergy(false,-1);
            mov = 2;
        }
        else if(lvl1[int(prot2->y())/tam][(int(prot2->x())+tam)/tam] == 3){
            prot2->setNumScale(5*prot2->getScale()/4);
            prot2->setScale(prot2->getScale());
            lvl1[int(prot2->y())/tam][(int(prot2->x())+tam)/tam] = 2;
            evalEnergy(false,1);
            mov = 2;
        }
        if(!disableMov) prot2->setX(prot2->x()+(tam*mov));
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

