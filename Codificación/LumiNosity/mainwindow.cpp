#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->barCanon1->hide();
    ui->barCanon2->hide();
    setupWindow(true);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete timeMovProta;
    delete timeSimuls;
    delete timeSimulsSierra;
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

void MainWindow::setupWindow(bool isInitMenu)
{
    scene=new QGraphicsScene;
    ui->graphicsView->setGeometry(0,0,tam*ancho+2,tam*alto+2);
    scene->setSceneRect(0,0,tam*ancho,tam*alto);
    ui->graphicsView->setScene(scene);
    if(!isInitMenu) ui->graphicsView->setBackgroundBrush(QBrush(QImage(":/images/Obstaculos/obs_1.png")));
    setFixedSize(tam*ancho+2,tam*alto+2);
    setWindowTitle("LumiNosity");

}

void MainWindow::setupMapa()
{
    setupWindow(false);
    setupObjectslvl1();
    prot1 = new prota(tam,tam,0);
    prot2 = new prota(tam,tam,1);
    ball = new canonBall(tam,tam);
    ball2 = new canonBall(tam,tam);
    prot1->setPos(tam*1,tam*1);
    prot2->setPos(tam*(ancho-2),tam*(alto-2));
    ball->setPos(tam*2,tam*2);
    ball2->setPos(tam*3,tam*3);

    timeMovProta = new QTimer;
    timeMovProta->start(75);
    timeSimuls = new QTimer;
    timeSimulsSierra = new QTimer;
    timeSimulsSierra->start(T);

    connect(timeMovProta,SIGNAL(timeout()),this,SLOT(anim()));
    connect(timeSimuls,SIGNAL(timeout()),this,SLOT(simul()));
    connect(timeSimulsSierra,SIGNAL(timeout()),this,SLOT(simulSierras()));

    scene->addItem(prot1);
    scene->addItem(prot2);
    scene->addItem(ball);
    scene->addItem(ball2);
    ball->hide();
    ball2->hide();
}

void MainWindow::setupObjectslvl1()
{
    string info1, objslvl1 = "../LumiNosity/lvl1.dat", subinfo1, objslvl2 = "../LumiNosity/lvl2.dat", objslvl3 = "../LumiNosity/lvl3.dat";
    int semilla = 7;
    bool write = true;
    contObs = 0, contCanons = 0, contPlats = 0, contSierras = 0, contResis = 0, contButts = 0;
    if(actualLvl == 1){
        info1 = decodeTxt(semilla,objslvl1);
        if(info1[0] == ',' && info1[1] == '0' && info1[2] == '0') write = false;
        codeTxt(semilla,objslvl1, write);
        info1 = decodeTxt(semilla,objslvl1);
        scaleFactor = 0.625;
    }
    else if(actualLvl == 2){
        info1 = decodeTxt(semilla,objslvl2);
        if(info1[0] == ',' && info1[1] == '0' && info1[2] == '0') write = false;
        codeTxt(semilla,objslvl2, write);
        info1 = decodeTxt(semilla,objslvl2);
        contChargers = 0;
        scaleFactor = 0.8;
    }
    else if(actualLvl == 3){
        info1 = decodeTxt(semilla,objslvl3);
        if(info1[0] == ',' && info1[1] == '0' && info1[2] == '0') write = false;
        codeTxt(semilla,objslvl3, write);
        info1 = decodeTxt(semilla,objslvl3);
        contChargers = 0;
        scaleFactor = 0.8;
    }
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
            else if(data==97 || (data>=70 && data<=71)){
                contSierras++;
            }
            else if(data==95 || data==92){
                contCanons+=2;
            }
            else if(data==94 || data==93 || data==83 || data==82){
                contPlats++;
            }
            else if(actualLvl > 1){
                if(data==60 || data==61){
                    contChargers++;
                }
            }
            subinfo1.clear();
        }
    }
    bombilla = new bulb(tam,tam);
    if(actualLvl > 1){
        cargador = new chargers*[contChargers];
        for(int i=0; i<contChargers; i++) cargador[i] = new chargers(tam,tam);
        contChargers = 0;
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
                    if(actualLvl == 1)resistor[contResis]->setHasButton(true,assignRes);
                    else if(actualLvl == 2) resistor[contResis]->setHasButton(true,2);
                    assignRes--;
                }
                scene->addItem(resistor[contResis]);
                contResis++;
            }
            else if(data>=50 && data <= 54){
                button[contButts]->setImg((data-50)*4);
                button[contButts]->setPos(anch*tam,alt*tam);
                if(actualLvl == 1){
                    if(contButts<3) button[contButts]->setNumButton(1);
                    else button[contButts]->setNumButton(2);
                }
                else if(actualLvl == 2){
                    button[contButts]->setNumButton(contButts+1);
                }
                scene->addItem(button[contButts]);
                contButts++;
            }
            else if(data==97 || (data>=70 && data<=71)){
                sierra[contSierras]->setPos(anch*tam,alt*tam);
                if(data>=70 && data<=71){
                    sierra[contSierras]->setTypeMov(data-69);
                    if(actualLvl == 2){
                        sierra[contSierras]->setCenterX(long(sierra[contSierras]->x()));
                        if(contSierras == 0 || contSierras == 5){
                            sierra[contSierras]->setCenterY(long(sierra[contSierras]->y())+2*tam);
                            sierra[contSierras]->setInitAng(90*M_PI/180);
                        }
                        else if(contSierras == 4 || contSierras == 9){
                            sierra[contSierras]->setCenterY(long(sierra[contSierras]->y())-tam);
                            sierra[contSierras]->setInitAng(-90*M_PI/180);
                        }
                        sierra[contSierras]->setA(2*tam);
                        sierra[contSierras]->setB(2*tam);
                        sierra[contSierras]->setVelAng(2*M_PI/periodo);
                    }
                }
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
            else if(data==94 || data==93 || data==83 || data==82){
                plat1[contPlats]->setAllowMov(3);
                if(data >90) plat1[contPlats]->setImg((data-93)*2);
                else if(data == 83 || data == 82){
                    plat1[contPlats]->setAllowMov(0);
                    plat1[contPlats]->setDir(-1);
                    plat1[contPlats]->setImg(2);
                    if(data == 83){
                        plat1[contPlats]->setDir(1);
                        plat1[contPlats]->setImg(3);
                    }
                }
                if(actualLvl == 2){
                    if(contPlats==0 || contPlats==4){
                        plat1[contPlats]->setNumBut(1);
                    }
                    else if(contPlats==3 || contPlats==7){
                        plat1[contPlats]->setNumBut(3);
                    }
                    else{
                        plat1[contPlats]->setNumBut(2);
                    }
                }
                plat1[contPlats]->setPos(anch*tam,alt*tam);
                plat1[contPlats]->setOriginY(plat1[contPlats]->y());
                plat1[contPlats]->setOriginX(plat1[contPlats]->x());
                contPlats++;
            }
            else if(data==98){
                bombilla->setImg(0);
                bombilla->setPos(anch*tam,alt*tam);
                scene->addItem(bombilla);
            }
            else if(actualLvl > 1){
                if(data == 60 || data == 61){
                    cargador[contChargers]->setPos(anch*tam,alt*tam);
                    cargador[contChargers]->setImg(0);
                    scene->addItem(cargador[contChargers]);
                    contChargers++;
                }
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
    for(int i=0; i<contSierras; i++) scene->addItem(sierra[i]);
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

void MainWindow::sceneScale2()
{
    if(!prot1->isVisible() && !prot2->isVisible() && scaleFactor == 0.8){
        ui->graphicsView->setSceneRect(tam*7,tam*4,tam*19,tam*12);
        scaleFactor = 1.25;
        ui->graphicsView->scale(scaleFactor,scaleFactor);

        ui->barCanon1->setGeometry(int(prot1->x())-9*tam/5,int(prot1->y())-tam/4,9*tam/4,tam/3);
        ui->barCanon2->setGeometry(int(prot2->x())+7*tam/10,int(prot2->y())+tam/4,9*tam/4,tam/3);
    }
    else{
        if(scaleFactor == 1.25) {
            scaleFactor = 0.8;
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
    for(int i=0; i<contObs; i++){
        scene->removeItem(mapa[i]);
        if(i<6) scene->removeItem(energy[i]);
        if(i<contCanons) scene->removeItem(canion[i]);
        if(i<contButts) scene->removeItem(button[i]);
        if(i<contResis) scene->removeItem(resistor[i]);
        if(i<contSierras) scene->removeItem(sierra[i]);
        if(i<contPlats) scene->removeItem(plat1[i]);
        if(i<contChargers) scene->removeItem(cargador[i]);
    }
    scene->removeItem(ball);
    scene->removeItem(ball2);
    scene->removeItem(prot1);
    scene->removeItem(prot2);
    scene->removeItem(bombilla);
    delete timeMovProta;
    delete timeSimuls;
    delete timeSimulsSierra;
    delete ball;
    delete ball2;
    delete bombilla;
    delete [] mapa;
    delete [] energy;
    delete [] canion;
    delete [] resistor;
    delete [] sierra;
    delete [] plat1;
    if(contChargers >= 0) delete [] cargador;
    delete [] button;
    delete prot1;
    delete prot2;
    canonKeys1 = false, canonKeys2 = false, bulb1 = false, bulb2 = false;
    movY = 0, movY2 = 0;
    if(actualLvl == 2) scaleFactor = 0.8;
    string newInfo;
    newInfo.append("lny9");
    newInfo.push_back(actualLvl+48);
    newInfo.push_back(lives+48);
    codeTxt(7,newInfo);
    setupMapa();
    switch(QMessageBox::question(
        this,
        tr("LumiNosity"),
        tr("Nivel Completado!.\n"
           "Siguiente Nivel?") ,
    QMessageBox::Yes | QMessageBox::No))
    {
    case QMessageBox::Yes:
            bombilla->setImg(0);
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
        for(int i=0; i<contObs; i++){
            scene->removeItem(mapa[i]);
            if(i<6) scene->removeItem(energy[i]);
            if(i<contCanons) scene->removeItem(canion[i]);
            if(i<contButts) scene->removeItem(button[i]);
            if(i<contResis) scene->removeItem(resistor[i]);
            if(i<contSierras) scene->removeItem(sierra[i]);
            if(i<contPlats) scene->removeItem(plat1[i]);
            if(i<contChargers) scene->removeItem(cargador[i]);
        }
        scene->removeItem(ball);
        scene->removeItem(ball2);
        scene->removeItem(prot1);
        scene->removeItem(prot2);
        scene->removeItem(bombilla);
        delete timeMovProta;
        delete timeSimuls;
        delete timeSimulsSierra;
        delete ball;
        delete ball2;
        delete bombilla;
        delete [] mapa;
        delete [] energy;
        delete [] canion;
        delete [] resistor;
        delete [] sierra;
        delete [] plat1;
        if(contChargers >= 0) delete [] cargador;
        delete [] button;
        delete prot1;
        delete prot2;
        canonKeys1 = false, canonKeys2 = false, bulb1 = false, bulb2 = false;
        movY = 0, movY2 = 0;
        string newInfo;
        if(lives == 0){
            actualLvl = 1;
            newInfo = "lny913";
            scaleFactor = 0.625;
        }
        else{
            newInfo.append("lny9");
            newInfo.push_back(actualLvl+48);
            newInfo.push_back(lives+48);
        }
        codeTxt(7,newInfo);
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

bool MainWindow::codeTxt(int semilla, string content)
{
    bool result=true;
    string texto,binario;
    try {
        texto=content;
        binario=text2bin(texto);
        binario=reglas_codifica(binario,semilla,true);
        texto=bin2text(binario);
        escribir(texto,"../LumiNosity/sudo.dat",false);
    }  catch (...) {
        result=false;
    }
    return result;
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


void MainWindow::anim()
{
    prot1->setAnim(0);
    prot2->setAnim(1);
    for(int i=0; i<contPlats; i++){
        if(plat1[i]->getAllowMov() >= 1){
            int dir = plat1[i]->getDir(), dist = plat1[i]->getAllowMov();
            if(plat1[i]->getTipo()==0){
                if(plat1[i]->getCountToChange() >= tam/2-2){
                    plat1[i]->setCountToChange(0);
                    plat1[i]->setDir(dir*(-1));
                }
                plat1[i]->setPos(plat1[i]->x()+2*dir*dist,plat1[i]->y());
                if(abs(dir)==double(dir)) plat1[i]->setImg(0);
                else plat1[i]->setImg(1);
            }
            else{
                if(plat1[i]->getCountToChange() >= tam/2-2){
                    plat1[i]->setCountToChange(0);
                    plat1[i]->setDir(dir*(-1));
                }
                plat1[i]->setPos(plat1[i]->x(),plat1[i]->y()+2*dir*dist);
                if(abs(dir)==double(dir)) plat1[i]->setImg(3);
                else plat1[i]->setImg(2);
            }
            plat1[i]->setCountToChange(plat1[i]->getCountToChange()+1);
        }
    }
    for(int i=0; i<contButts; i++){
        if(button[i]->getStartAnim()){
            button[i]->setAnim();
        }
    }
    for(int i=0; i<contSierras; i++) sierra[i]->setAnim();
    if(bombilla->getTipo() == 2){
        nextLvl();
    }
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
        for(int i=120; i<contObs;i++){
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
                        if(actualLvl == 1) resistor[i2]->replace(1+resistor[i2]->getNumButton());
                        else if(actualLvl == 2) resistor[i2]->replace(3);
                        lvl1[int(resistor[i2]->y())/tam][int(resistor[i2]->x())/tam] = 1;
                    }
                }
                for(int i3=0; i3<contPlats; i3++){
                    if(plat1[i3]->getNumBut() != 0 && plat1[i3]->getNumBut() == button[i]->getNumButton()){
                        if(!plat1[i3]->getTrigger()){
                            plat1[i3]->setTrigger(true);
                            plat1[i3]->setAllowMov(2);
                        }
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
                        if(actualLvl == 1) resistor[i2]->replace(1+resistor[i2]->getNumButton());
                        else if(actualLvl == 2) resistor[i2]->replace(3);
                        lvl1[int(resistor[i2]->y())/tam][int(resistor[i2]->x())/tam] = 1;
                    }
                }
                for(int i3=0; i3<contPlats; i3++){
                    if(plat1[i3]->getNumBut() != 0 && plat1[i3]->getNumBut() == button[i]->getNumButton()){
                        if(!plat1[i3]->getTrigger()){
                            plat1[i3]->setTrigger(true);
                            plat1[i3]->setAllowMov(2);
                        }
                    }
                }
            }
        }
    }
    else if(!ball->getActivate() && !ball2->getActivate()){
        timeSimuls->stop();
    }
}

void MainWindow::simulSierras()
{
    for(int i=0; i<contSierras; i++){
        if(sierra[i]->getTypeMov() == 1){ //MCU or Mov Elip Unif
            sierra[i]->setX(sierra[i]->getA()*cos(sierra[i]->getVelAng()*sierra[i]->getCounter()*T+sierra[i]->getInitAng()+sierra[i]->getVelAng()*T)+sierra[i]->getCenterX());
            sierra[i]->setY(sierra[i]->getB()*sin(sierra[i]->getVelAng()*sierra[i]->getCounter()*T+sierra[i]->getInitAng()+sierra[i]->getVelAng()*T)+sierra[i]->getCenterY());
            sierra[i]->setCounter(sierra[i]->getCounter()+1);
            if(sierra[i]->getCounter() >= periodo/T) sierra[i]->setCounter(0);
        }
        else if(sierra[i]->getTypeMov() == 2){ //Mov Pendular

        }
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
            if(actualLvl == 1) sceneScale1();
            else if(actualLvl == 2) sceneScale2();
        }
        else if(qFabs(bombilla->x()-prot1->x()) <= tam && qFabs(bombilla->y()-prot1->y()) <= tam){
            bulb1 = !bulb1;
            prot1->setVisible(!prot1->isVisible());
            if(bulb1 && (!(qFabs(bombilla->x()-prot2->x()) <= tam && qFabs(bombilla->y()-prot2->y()) <= tam) || prot2->isVisible())) bombilla->setImg(1);
            else if(!bulb1 && (!(qFabs(bombilla->x()-prot2->x()) <= tam && qFabs(bombilla->y()-prot2->y()) <= tam) || prot2->isVisible())) bombilla->setImg(0);
            else if(bulb1 && (qFabs(bombilla->x()-prot2->x()) <= tam && qFabs(bombilla->y()-prot2->y()) <= tam && !prot2->isVisible())) bombilla->setImg(2);
        }
        else if(actualLvl > 1){
            for(int i=0; i<contChargers; i++){
                if(qFabs(cargador[i]->x()-prot1->x()) <= tam && qFabs(cargador[i]->y()-prot1->y()) <= tam){
                    if(cargador[i]->getTipo() == 0){
                        if(actualLvl == 2){
                            for(int i2=0; i2<contPlats;i2++){
                                if((i2>=1 && i2<=2) || (i2>=5 && i2<=6)) plat1[i2]->setAllowMov(1);
                            }
                        }
                        cargador[i]->setImg(1);
                        cargador[i]->setLastProt(1);
                    }
                    else if(cargador[i]->getTipo() == 1 && cargador[i]->getLastProt() != 1){
                        if(actualLvl == 2){
                            for(int i2=0; i2<contPlats;i2++){
                                if((i2>=1 && i2<=2) || (i2>=5 && i2<=6)){
                                    plat1[i2]->setY(plat1[i2]->getOriginY());
                                    plat1[i2]->setDir(-1);
                                    plat1[i2]->setCountToChange(0);
                                    plat1[i2]->setAllowMov(3);
                                }
                            }
                        }
                        cargador[i]->setImg(2);
                    }
                }
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
            if(actualLvl == 1) sceneScale1();
            else if(actualLvl == 2) sceneScale2();
        }
        else if(qFabs(bombilla->x()-prot2->x()) <= tam && qFabs(bombilla->y()-prot2->y()) <= tam){
            bulb2 = !bulb2;
            prot2->setVisible(!prot2->isVisible());
            if(bulb2 && (!(qFabs(bombilla->x()-prot1->x()) <= tam && qFabs(bombilla->y()-prot1->y()) <= tam) || prot1->isVisible())) bombilla->setImg(1);
            else if(!bulb2 && (!(qFabs(bombilla->x()-prot1->x()) <= tam && qFabs(bombilla->y()-prot1->y()) <= tam) || prot1->isVisible())) bombilla->setImg(0);
            else if(bulb2 && (qFabs(bombilla->x()-prot1->x()) <= tam && qFabs(bombilla->y()-prot1->y()) <= tam && !prot1->isVisible())) bombilla->setImg(2);
        }
        else if(actualLvl > 1){
            for(int i=0; i<contChargers; i++){
                if(qFabs(cargador[i]->x()-prot2->x()) <= tam && qFabs(cargador[i]->y()-prot2->y()) <= tam){
                    if(cargador[i]->getTipo() == 0){
                        if(actualLvl == 2){
                            for(int i2=0; i2<contPlats;i2++){
                                if((i2>=1 && i2<=2) || (i2>=5 && i2<=6)) plat1[i2]->setAllowMov(1);
                            }
                        }
                        cargador[i]->setImg(1);
                        cargador[i]->setLastProt(2);
                    }
                    else if(cargador[i]->getTipo() == 1 && cargador[i]->getLastProt() != 2){
                        if(actualLvl == 2){
                            for(int i2=0; i2<contPlats;i2++){
                                if((i2>=1 && i2<=2) || (i2>=5 && i2<=6)){
                                    plat1[i2]->setY(plat1[i2]->getOriginY());
                                    plat1[i2]->setDir(-1);
                                    plat1[i2]->setCountToChange(0);
                                    plat1[i2]->setAllowMov(3);
                                }
                            }
                        }
                        cargador[i]->setImg(2);
                    }
                }
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
    setupMapa();
    ui->newGame->hide();
    ui->newGame->setEnabled(false);
    ui->loadGame->hide();
    ui->loadGame->setEnabled(false);
    ui->exit->hide();
    ui->exit->setEnabled(false);
}


void MainWindow::on_loadGame_clicked()
{
    string linkInfo = "../LumiNosity/sudo.dat", getInfo;
    int semilla = 7;
    bool write = true;
    getInfo = decodeTxt(semilla,linkInfo);
    if(getInfo[0] == 'l' && getInfo[1] == 'n' && getInfo[2] == 'y' && getInfo[3] == '9') write = false;
    codeTxt(semilla,linkInfo,write);
    getInfo = decodeTxt(semilla,linkInfo);
    actualLvl = getInfo[4]-48;
    lives = getInfo[5]-48;
    setupMapa();
    ui->newGame->hide();
    ui->newGame->setEnabled(false);
    ui->loadGame->hide();
    ui->loadGame->setEnabled(false);
    ui->exit->hide();
    ui->exit->setEnabled(false);
}

