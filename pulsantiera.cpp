#include "pulsantiera.h"
#include "gestoregiocatori.h"
#include "scambiocorrente.h"

#include <QPushButton>

Pulsantiera::Pulsantiera(ScambioCorrente* curr, GestoreGiocatori* g) : scambioCorrente(curr),gestoreGiocatori(g)
{
    // PULSANTI AZIONE

    QGridLayout* pulsantiAzione = new QGridLayout();
    QPushButton* azioneBat = new QPushButton("&BAT");
    QPushButton* azioneRic = new QPushButton("&RIC");
    QPushButton* azioneAtt = new QPushButton("&ATT");
    QPushButton* azioneMur = new QPushButton("&MUR");

    azioneBat->setShortcut(QKeySequence(Qt::Key_B));
    azioneRic->setShortcut(QKeySequence(Qt::Key_R));
    azioneAtt->setShortcut(QKeySequence(Qt::Key_A));
    azioneMur->setShortcut(QKeySequence(Qt::Key_M));

    pulsantiAzione->addWidget(azioneBat,0,0);
    pulsantiAzione->addWidget(azioneRic,0,1);
    pulsantiAzione->addWidget(azioneAtt,1,0);
    pulsantiAzione->addWidget(azioneMur,1,1);


    // PULSANTI ESITO

    QGridLayout* pulsantiEsito = new QGridLayout();
    QPushButton* esitoPiu = new QPushButton("+");
    QPushButton* esitoDoppioPiu = new QPushButton("#");
    QPushButton* esitoMeno = new QPushButton("-");
    QPushButton* esitoDoppioMeno = new QPushButton("=");
    QPushButton* esitoP1 = new QPushButton("P&1");
    QPushButton* esitoP2 = new QPushButton("P&2");

    esitoPiu->setShortcut(QKeySequence(Qt::Key_Plus));
    esitoDoppioPiu->setShortcut(QKeySequence(Qt::Key_NumberSign));
    esitoMeno->setShortcut(QKeySequence(Qt::Key_Minus));
    esitoDoppioMeno->setShortcut(QKeySequence(Qt::Key_Equal));

    pulsantiEsito->addWidget(esitoPiu,0,0);
    pulsantiEsito->addWidget(esitoDoppioPiu,0,1);
    pulsantiEsito->addWidget(esitoMeno,1,0);
    pulsantiEsito->addWidget(esitoDoppioMeno,1,1);
    pulsantiEsito->addWidget(esitoP1,2,0);
    pulsantiEsito->addWidget(esitoP2,2,1);

    connect(azioneBat,SIGNAL(clicked(bool)),this,SLOT(clickBat()));
    connect(azioneRic,SIGNAL(clicked(bool)),this,SLOT(clickRic()));
    connect(azioneAtt,SIGNAL(clicked(bool)),this,SLOT(clickAtt()));
    connect(azioneMur,SIGNAL(clicked(bool)),this,SLOT(clickMur()));

    connect(esitoPiu,SIGNAL(clicked(bool)),this,SLOT(clickPiu()));
    connect(esitoDoppioPiu,SIGNAL(clicked(bool)),this,SLOT(clickDoppioPiu()));
    connect(esitoMeno,SIGNAL(clicked(bool)),this,SLOT(clickMeno()));
    connect(esitoDoppioMeno,SIGNAL(clicked(bool)),this,SLOT(clickDoppioMeno()));

    connect(esitoP1,SIGNAL(clicked(bool)),this,SLOT(clickP1()));
    connect(esitoP2,SIGNAL(clicked(bool)),this,SLOT(clickP2()));


    addLayout(pulsantiAzione);
    addLayout(pulsantiEsito);
}

void Pulsantiera::clickBat()
{
    prossimoPunto.clear();
    if (gestoreGiocatori->getSelectedPlayer() == "") return;
    prossimoPunto.append(new QStandardItem(gestoreGiocatori->getSelectedPlayer()));
    prossimoPunto.append(new QStandardItem("Battuta"));
}

void Pulsantiera::clickRic()
{
    prossimoPunto.clear();
    if (gestoreGiocatori->getSelectedPlayer() == "") return;
    prossimoPunto.append(new QStandardItem(gestoreGiocatori->getSelectedPlayer()));
    prossimoPunto.append(new QStandardItem("Ricezione"));
}

void Pulsantiera::clickAtt()
{
    prossimoPunto.clear();
    if (gestoreGiocatori->getSelectedPlayer() == "") return;
    prossimoPunto.append(new QStandardItem(gestoreGiocatori->getSelectedPlayer()));
    prossimoPunto.append(new QStandardItem("Attacco"));
}

void Pulsantiera::clickMur()
{
    prossimoPunto.clear();
    if (gestoreGiocatori->getSelectedPlayer() == "") return;
    prossimoPunto.append(new QStandardItem(gestoreGiocatori->getSelectedPlayer()));
    prossimoPunto.append(new QStandardItem("Muro"));
}

void Pulsantiera::clickPiu()
{
    if(!prossimoPunto.isEmpty())
    {
        prossimoPunto.append(new QStandardItem("+"));
        scambioCorrente->aggiungiRiga(prossimoPunto);
        prossimoPunto.clear();
    }
}

void Pulsantiera::clickDoppioPiu()
{
    if(!prossimoPunto.isEmpty())
    {
        prossimoPunto.append(new QStandardItem("#"));
        scambioCorrente->aggiungiRiga(prossimoPunto);
        prossimoPunto.clear();
    }
}

void Pulsantiera::clickMeno()
{
    if(!prossimoPunto.isEmpty())
    {
        prossimoPunto.append(new QStandardItem("-"));
        scambioCorrente->aggiungiRiga(prossimoPunto);
        prossimoPunto.clear();
    }
}

void Pulsantiera::clickDoppioMeno()
{
    if(!prossimoPunto.isEmpty())
    {
        prossimoPunto.append(new QStandardItem("="));
        scambioCorrente->aggiungiRiga(prossimoPunto);
        prossimoPunto.clear();
    }
}

void Pulsantiera::clickP1()
{
    QVector<QVector<QString>> vector = scambioCorrente->inVector();
    while(!vector.isEmpty())
    {
        gestoreGiocatori->aggiungiDato(vector.first());
        vector.removeFirst();
    }
    scambioCorrente->incrementaP1();
}

void Pulsantiera::clickP2()
{
    QVector<QVector<QString>> vector = scambioCorrente->inVector();
    while(!vector.isEmpty())
    {
        gestoreGiocatori->aggiungiDato(vector.first());
        vector.pop_front();
    }
    scambioCorrente->incrementaP2();
}
