#include "mainwindow.h"
#include "scambiocorrente.h"
#include "pulsantiera.h"

#include <QMenu>
#include <QMenuBar>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowIcon(QIcon("volley-ball.ico")) ;
    QWidget* centrale = new QWidget();
    setCentralWidget(centrale);
    QHBoxLayout* mainLayout = new QHBoxLayout();
    centrale->setLayout(mainLayout);

    ScambioCorrente* scambioCorrente = new ScambioCorrente();

    gestoreGiocatori = new GestoreGiocatori();

    Pulsantiera* pulsantiera = new Pulsantiera(scambioCorrente,gestoreGiocatori);

    mainLayout->addLayout(scambioCorrente);
    mainLayout->addLayout(pulsantiera);
    mainLayout->addLayout(gestoreGiocatori,1);

    QMenu* filemenu = menuBar()->addMenu("&File");
        QAction* EsportaCSV = new QAction("Esporta &dati in .CSV");
        filemenu->addAction(EsportaCSV);
        connect(EsportaCSV,SIGNAL(triggered()),gestoreGiocatori,SLOT(esportaTabella()));
        QAction* EsportaGrafici = new QAction("Esporta &grafici in .JPG");
        filemenu->addAction(EsportaGrafici);
        connect(EsportaGrafici,SIGNAL(triggered()),gestoreGiocatori,SLOT(esportaGrafici()));
        QMenu* modificamenu = menuBar()->addMenu("M&odifica");
        QAction* preset = new QAction("&Carica preset");
        modificamenu->addAction(preset);
        connect(preset,SIGNAL(triggered()),gestoreGiocatori,SLOT(caricaPreset()));
        QAction* modificaPreset = new QAction("&Modifica preset");
        modificamenu->addAction(modificaPreset);
        connect(modificaPreset,SIGNAL(triggered(bool)),gestoreGiocatori,SLOT(modificaPreset()));
}


