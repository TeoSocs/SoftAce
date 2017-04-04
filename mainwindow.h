#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gestoregiocatori.h"

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
private:
    GestoreGiocatori* gestoreGiocatori;
};

#endif // MAINWINDOW_H
