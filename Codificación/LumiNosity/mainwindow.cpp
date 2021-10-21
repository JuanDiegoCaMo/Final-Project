#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ball = new canonBall(tam,tam);
    ball2 = new canonBall(tam,tam);
    bombilla = new bulb(tam,tam);

    ui->setupUi(this);
    timeMovProta = new QTimer;
    timeMovProta->start(75);
    timeSimuls = new QTimer;

    connect(timeMovProta,SIGNAL(timeout()),this,SLOT(animProta()));
    connect(timeSimuls,SIGNAL(timeout()),this,SLOT(simul()));
    setupWindow();
    setupMapa();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete timeMovProta;
    delete timeSimuls;
    delete ball;
    delete ball2;
    delete bombilla;
    delete [] mapa;
    delete [] energy;
    delete [] canion;
    delete [] resistor;
    delete [] sierra;
    delete [] plat1;
    delete [] cargador;
    delete [] button;
    delete prot1;
    delete prot2;
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
    ball2->setPos(tam*3,tam*3);
    scene->addItem(prot1);
    scene->addItem(prot2);
    scene->addItem(ball);
    scene->addItem(ball2);
    ball->hide();
    ball2->hide();
}

void MainWindow::setupObjectslvl1()
{
    string info1, objslvl1 = "../LumiNosity/lvl1.dat", subinfo1;
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
    int anch = 0, alt = 0, assignRes = 2;
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
                if(data == 96){
                    resistor[contResis]->setHasButton(true,assignRes);
                    assignRes--;
                }
                scene->addItem(resistor[contResis]);
                contResis++;
            }
            else if(data>=50 && data <= 54){
                button[contButts]->setImg((data-50)*4);
                button[contButts]->setPos(anch*tam,alt*tam);
                if(contButts<=3) button[contButts]->setNumButton(1);
                else button[contButts]->setNumButton(2);
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
                if(data==95){
                    canion[contCanons+1]->setPos(anch*tam+3*tam/8,alt*tam+tam/20);
                    canion[contCanons+1]->setImg(0,true);
                    ui->barCanon1->setGeometry(int(canion[contCanons]->x())-5,int(canion[contCanons]->y())+tam,9*tam/5,tam/3);
                }
                else{
                    canion[contCanons+1]->setPos(anch*tam-3*tam/8,alt*tam+tam/20);
                    canion[contCanons+1]->setImg(2,true);
                    ui->barCanon2->setGeometry(int(canion[contCanons]->x())-5,int(canion[contCanons]->y())+tam,9*tam/5,tam/3);
                }
                contCanons+=2;
            }
            else if(data<=94 && data>= 93){
                plat1[contPlats]->setImg((data-93)*2);
                plat1[contPlats]->setPos(anch*tam,alt*tam);
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
    ui->barCanon1->setValue(0);
    ui->barCanon2->setValue(0);
    geoCan1 = ui->barCanon1->saveGeometry();
    geoCan2 = ui->barCanon2->saveGeometry();
    ui->barCanon1->hide();
    ui->barCanon2->hide();
    for(int i=0; i<contCanons; i++) scene->addItem(canion[i]);
    for(int i=0; i<contPlats; i++) scene->addItem(plat1[i]);
    energy = new obstacles*[6];
    for(int i=0;i<6; i++){
        energy[i] = new obstacles(tam,tam);
        energy[i]->setImgEnergy();
        if(i<3) energy[i]->setPos(i*tam,0);
        else    energy[i]->setPos(ancho*tam-(i-3)*tam-tam,0);
        scene->addItem(energy[i]);
    }
}

void MainWindow::sceneScale1()
{
    if(!prot1->isVisible() && !prot2->isVisible() && scaleFactor == 0.625){
        ui->graphicsView->setSceneRect(tam*4,tam*5,tam*19,tam*11);
        scaleFactor = 1.6;
        ui->graphicsView->scale(scaleFactor,scaleFactor);

        ui->barCanon1->setGeometry(int(prot1->x())-tam*2+2*tam/10,int(prot1->y())+tam,9*tam/4,tam/3);
        ui->barCanon2->setGeometry(int(prot2->x())+tam*7,int(prot2->y())+tam,9*tam/4,tam/3);
    }
    else{
        if(scaleFactor == 1.6) {
            scaleFactor = 0.625;
            ui->graphicsView->scale(scaleFactor,scaleFactor);
            ui->graphicsView->setSceneRect(0,0,tam*ancho,tam*alto);
            ui->barCanon1->restoreGeometry(geoCan1);
            ui->barCanon2->restoreGeometry(geoCan2);
        }
    }
}

void MainWindow::nextLvl()
{
    actualLvl++;
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
    switch(QMessageBox::question(
        this,
        tr("LumiNosity"),
        tr("Nivel Completado!.\n"
           "Siguiente Nivel?") ,
    QMessageBox::Yes | QMessageBox::No))
    {
    case QMessageBox::Yes:
            lives = 3;
            bombilla->setImg(0);
            canonKeys1 = false, canonKeys2 = false, bulb1 = false, bulb2 = false;
            movY = 0, movY2 = 0;
            break;
    case QMessageBox::No:
        this->close();
        break;
    }
}

bool MainWindow::evalEnergy(bool isProt1, int modify)
{
    if(isProt1){
        if(modify<0) energy[prot1->getEnergy()-1]->hide();
        else if(modify>0)    energy[prot1->getEnergy()]->show();
        prot1->setEnergy(prot1->getEnergy()+modify);
    }
    else{
        if(modify<0) energy[prot2->getEnergy()+2]->hide();
        else if(modify>0)    energy[prot2->getEnergy()+3]->show();
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
                        canonKeys1 = false, canonKeys2 = false, bulb1 = false, bulb2 = false;
                        movY = 0, movY2 = 0;
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
    for(int i=0; i<contPlats; i++){
        int dir = plat1[i]->getDir();
        if(plat1[i]->getTipo()==0){
            for(int i2=0; i2<contObs; i2++){
                if(mapa[i2]->getTipo() == 0 && mapa[i2]->x() == plat1[i]->x()+qreal(5*dir)){
                    dir = dir*(-1);
                    break;
                }
            }
            plat1[i]->setPos(plat1[i]->x()+5*dir,plat1[i]->y());
            if(abs(dir)==double(dir)) plat1[i]->setImg(0);
            else plat1[i]->setImg(1);
        }
        else{
            for(int i2=0; i2<contObs; i2++){
                if(mapa[i2]->getTipo() == 0 && mapa[i2]->y() == plat1[i]->y()+qreal(5*dir)){
                    dir = dir*(-1);
                    break;
                }
            }
            plat1[i]->setPos(plat1[i]->x(),plat1[i]->y()+5*dir);
            if(abs(dir)==double(dir)) plat1[i]->setImg(2);
            else plat1[i]->setImg(3);
        }
        plat1[i]->setDir(dir);
    }
    for(int i=0; i<contButts; i++){
        if(button[i]->getStartAnim()){
            button[i]->setAnim();
        }
    }
    for(int i=0; i<contSierras; i++) sierra[i]->setAnim();
}

void MainWindow::simul()
{
    float h = ui->graphicsView->height(), g = 10;
    float x1, x2, y1, y2;
    if(ball->getActivate()){
        ball->show();
        x1 = ball->getX0()+ball->getVx0()*ball->getN()*0.007*T;
        y1 = ball->getY0()+ball->getVy0()*ball->getN()*0.007*T-0.5*g*ball->getN()*0.007*T*ball->getN()*0.007*T;
        ball->setPos(int(x1),int(h-y1-ball->getHeight()));
        ball->setN(ball->getN()+1);
        for(int i=149; i<contObs;i++){
            if(mapa[i]->getTipo() == 0){
                if(mapa[i]->collidesWithItem(ball)){
                    ball->setActivate(false);
                    ball->hide();
                }
            }
        }
        for(int i=0; i<contSierras; i++){
            if(sierra[i]->collidesWithItem(ball)){
                ball->setActivate(false);
                ball->hide();
            }
        }
        for(int i=0; i<contPlats; i++){
            if(plat1[i]->collidesWithItem(ball)){
                ball->setActivate(false);
                ball->hide();
            }
        }
        for(int i=0; i<contButts; i++){
            if(button[i]->collidesWithItem(ball)){
                ball->setActivate(false);
                ball->hide();
                button[i]->setStartAnim(true);
                for(int i2=0; i2<contResis; i2++){
                    if(resistor[i2]->getHasButton() && resistor[i2]->getNumButton() == button[i]->getNumButton()){
                        resistor[i2]->replace(1+resistor[i2]->getNumButton());
                        lvl1[int(resistor[i2]->y())/tam][int(resistor[i2]->x())/tam] = 1;
                    }
                }
            }
        }
    }
    if(ball2->getActivate()){
        ball2->show();
        x2 = ball2->getX0()+ball2->getVx0()*ball2->getN()*0.007*T;
        y2 = ball2->getY0()+ball2->getVy0()*ball2->getN()*0.007*T-0.5*g*ball2->getN()*0.007*T*ball2->getN()*0.007*T;
        ball2->setPos(int(x2),int(h-y2-ball2->getHeight()));
        ball2->setN(ball2->getN()+1);
        for(int i=149; i<contObs;i++){
            if(mapa[i]->getTipo() == 0){
                if(mapa[i]->collidesWithItem(ball2)){
                    ball2->setActivate(false);
                    ball2->hide();
                }
            }
        }
        for(int i=0; i<contSierras; i++){
            if(sierra[i]->collidesWithItem(ball2)){
                ball2->setActivate(false);
                ball2->hide();
            }
        }
        for(int i=0; i<contPlats; i++){
            if(plat1[i]->collidesWithItem(ball2)){
                ball2->setActivate(false);
                ball2->hide();
            }
        }
        for(int i=0; i<contButts; i++){
            if(button[i]->collidesWithItem(ball2)){
                ball2->setActivate(false);
                ball2->hide();
                button[i]->setStartAnim(true);
                for(int i2=0; i2<contResis; i2++){
                    if(resistor[i2]->getHasButton() && resistor[i2]->getNumButton() == button[i]->getNumButton()){
                        resistor[i2]->replace(1+resistor[i2]->getNumButton());
                        lvl1[int(resistor[i2]->y())/tam][int(resistor[i2]->x())/tam] = 1;
                    }
                }
            }
        }
    }
    else if(!ball->getActivate() && !ball2->getActivate()){
        timeSimuls->stop();
    }
}

void MainWindow::keyPressEvent(QKeyEvent *key){
    short int mov = 1, limitRot = 60;
    bool disableMov = false;
    if(key->key() == Qt::Key_Q){ //Vincular Player 1
        if(lvl1[(int(prot1->y())+tam)/tam][int(prot1->x())/tam] == -1 || lvl1[(int(prot1->y())-tam)/tam][int(prot1->x())/tam] == -1 || lvl1[int(prot1->y())/tam][(int(prot1->x())+tam)/tam] == -1 || lvl1[int(prot1->y())/tam][(int(prot1->x())-tam)/tam] == -1){
            prot1->setVisible(!prot1->isVisible());
            canonKeys1 = !canonKeys1;
            if(!canonKeys1){
                int elCanon1 = 0;
                movY = 0;
                for(int i=0; i<contCanons; i++){
                    if(canion[i]->x() == prot1->x()+11*tam/8 && canion[i]->y() == prot1->y()+tam/20) elCanon1 = i;
                }
                canion[elCanon1]->setRotation(0);
                canion[elCanon1]->setImg(0,true);
                canion[elCanon1-1]->setImg(0,false);
                ui->barCanon1->hide();
            }
            sceneScale1();
        }
        else if(bombilla->x()-prot1->x() <= tam && bombilla->y()-prot1->y() <= tam){
            bulb1 = !bulb1;
            prot1->setVisible(!prot1->isVisible());
            if(prot2->isVisible() && bulb1) bombilla->setImg(1);
            else if(prot2->isVisible() && !bulb1) bombilla->setImg(0);
            else if(!prot2->isVisible() && bulb1) bombilla->setImg(2);
            if(bombilla->getTipo() == 2){
                nextLvl();
            }
        }
    }
    else if(key->key() == Qt::Key_U){ //Vincular Player 2
        if(lvl1[(int(prot2->y())+tam)/tam][int(prot2->x())/tam] == -1 || lvl1[(int(prot2->y())-tam)/tam][int(prot2->x())/tam] == -1 || lvl1[int(prot2->y())/tam][(int(prot2->x())+tam)/tam] == -1 || lvl1[int(prot2->y())/tam][(int(prot2->x())-tam)/tam] == -1){
            prot2->setVisible(!prot2->isVisible());
            canonKeys2 = !canonKeys2;
            if(!canonKeys2){
                int elCanon1 = 0;
                movY2 = 0;
                for(int i=0; i<contCanons; i++){
                    if(canion[i]->x() == prot2->x()-11*tam/8 && canion[i]->y() == prot2->y()+tam/20) elCanon1 = i;
                }
                canion[elCanon1]->setRotation(0);
                canion[elCanon1]->setImg(2,true);
                canion[elCanon1-1]->setImg(0,false);
                ui->barCanon2->hide();
            }
            sceneScale1();
        }
        else if(bombilla->x()-prot2->x() <= tam && bombilla->y()-prot2->y() <= tam){
            bulb2 = !bulb2;
            prot2->setVisible(!prot2->isVisible());
            if(prot1->isVisible() && bulb2) bombilla->setImg(1);
            else if(prot1->isVisible() && !bulb2) bombilla->setImg(0);
            else if(!prot1->isVisible() && bulb2) bombilla->setImg(2);
            if(bombilla->getTipo() == 2){
                nextLvl();
            }
        }
    }
    if(!canonKeys1){
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
            if(!disableMov && !bulb1) prot1->setY(prot1->y()-(tam*mov));
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
            if(!disableMov && !bulb1) prot1->setX(prot1->x()-(tam*mov));
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
            if(!disableMov && !bulb1) prot1->setY(prot1->y()+(tam*mov));
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
            if(!disableMov && !bulb1) prot1->setX(prot1->x()+(tam*mov));
        }
    }
    else if(prot1->getEnergy() >= 2){
        int elCanon1 = 0;
        ui->barCanon1->show();
        for(int i=0; i<contCanons; i++){
            if(canion[i]->x() == prot1->x()+11*tam/8 && canion[i]->y() == prot1->y()+tam/20) elCanon1 = i;
        }
        ui->barCanon1->setValue(canion[elCanon1]->getPower());
        canion[elCanon1]->setImg(1,true);
        canion[elCanon1-1]->setImg(1,false);
        canion[elCanon1]->setTransformOriginPoint(0,5*tam/8);
        if(key->key() == Qt::Key_W){
            if(canion[elCanon1]->rotation() > -limitRot){
                movY += 1;
                canion[elCanon1]->setRotation(canion[elCanon1]->rotation()-2);
            }
        }
        else if(key->key() == Qt::Key_A && canion[elCanon1]->getPower() > 0){
            canion[elCanon1]->setPower(canion[elCanon1]->getPower()-2);
        }
        else if(key->key() == Qt::Key_S){
            if(canion[elCanon1]->rotation() < 0){
                movY -= 1;
                canion[elCanon1]->setRotation(canion[elCanon1]->rotation()+2);
            }
        }
        else if(key->key() == Qt::Key_D && canion[elCanon1]->getPower() < 100){
            canion[elCanon1]->setPower(canion[elCanon1]->getPower()+2);
        }
        else if(key->key() == Qt::Key_E){
            if(!ball->getActivate()){
            ball->setActivate(true);
            ball->setX0(int(canion[elCanon1-1]->x()+tam/2)+5*tam/8-movY);
            ball->setY0(ui->graphicsView->height()-int(canion[elCanon1-1]->y()-movY+tam/2));
            ball->setN(0);
            ball->setVx0(double(qreal(canion[elCanon1]->getPower())*qCos(qFabs(canion[elCanon1]->rotation())*M_PI/180)));
            ball->setVy0(double(qreal(canion[elCanon1]->getPower())*qSin(qFabs(canion[elCanon1]->rotation())*M_PI/180)));
            timeSimuls->start(T);
            }
        }
        ui->barCanon1->setValue(canion[elCanon1]->getPower());
    }
    if(!canonKeys2){
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
            if(!disableMov && !bulb2) prot2->setY(prot2->y()-(tam*mov));
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
            if(!disableMov && !bulb2) prot2->setX(prot2->x()-(tam*mov));
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
            if(!disableMov && !bulb2) prot2->setY(prot2->y()+(tam*mov));
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
            if(!disableMov && !bulb2) prot2->setX(prot2->x()+(tam*mov));
        }
    }
    else if(prot2->getEnergy() >= 2){
        int elCanon1 = 0;
        ui->barCanon2->show();
        for(int i=0; i<contCanons; i++){
            if(canion[i]->x() == prot2->x()-11*tam/8 && canion[i]->y() == prot2->y()+tam/20) elCanon1 = i;
        }
        ui->barCanon2->setValue(canion[elCanon1]->getPower());
        canion[elCanon1]->setImg(3,true);
        canion[elCanon1-1]->setImg(1,false);
        canion[elCanon1]->setTransformOriginPoint(tam,5*tam/8);
        if(key->key() == Qt::Key_I){
            if(canion[elCanon1]->rotation() < limitRot){
                movY2 += 1;
                canion[elCanon1]->setRotation(canion[elCanon1]->rotation()+2);
            }
        }
        else if(key->key() == Qt::Key_J && canion[elCanon1]->getPower() > 0){
            canion[elCanon1]->setPower(canion[elCanon1]->getPower()-2);
        }
        else if(key->key() == Qt::Key_K){
            if(canion[elCanon1]->rotation() > 0){
                movY2 -= 1;
                canion[elCanon1]->setRotation(canion[elCanon1]->rotation()-2);
            }
        }
        else if(key->key() == Qt::Key_L && canion[elCanon1]->getPower() < 100){
            canion[elCanon1]->setPower(canion[elCanon1]->getPower()+2);
        }
        else if(key->key() == Qt::Key_O){
                if(!ball2->getActivate()){
                ball2->setActivate(true);
                ball2->setX0(int(canion[elCanon1-1]->x()+tam/2)-tam+movY2);
                ball2->setY0(ui->graphicsView->height()-int(canion[elCanon1-1]->y()-movY2+tam/2));
                ball2->setN(0);
                ball2->setVx0(double(-qreal(canion[elCanon1]->getPower())*qCos(canion[elCanon1]->rotation()*M_PI/180)));
                ball2->setVy0(double(qreal(canion[elCanon1]->getPower())*qSin(canion[elCanon1]->rotation()*M_PI/180)));
                timeSimuls->start(T);
                }
        }
        ui->barCanon2->setValue(canion[elCanon1]->getPower());
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

