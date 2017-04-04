#-------------------------------------------------
#
# Project created by QtCreator 2016-11-15T15:59:02
#
#-------------------------------------------------

QT += core gui
QT += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SoftAce
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    scambiocorrente.cpp \
    pulsantiera.cpp \
    gestoregiocatori.cpp \
    dialoggrafici.cpp

HEADERS  += mainwindow.h \
    scambiocorrente.h \
    pulsantiera.h \
    gestoregiocatori.h \
    dialoggrafici.h

RC_FILE = SoftAce.rc
