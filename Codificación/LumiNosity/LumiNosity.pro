QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    canon.cpp \
    canonball.cpp \
    chargers.cpp \
    ene_resistor.cpp \
    ene_sierra.cpp \
    main.cpp \
    mainwindow.cpp \
    movilplat.cpp \
    obstacles.cpp \
    prota.cpp

HEADERS += \
    canon.h \
    canonball.h \
    chargers.h \
    ene_resistor.h \
    ene_sierra.h \
    mainwindow.h \
    movilplat.h \
    obstacles.h \
    prota.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    imgs.qrc
