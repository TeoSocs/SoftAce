#include "scambiocorrente.h"

#include <QHBoxLayout>
#include <QToolButton>
#include <QPushButton>
#include <QTableView>
#include <QStandardItemModel>
#include <QLCDNumber>



ScambioCorrente::ScambioCorrente()
{
    QHBoxLayout* segnaPunti = new QHBoxLayout();
    QVBoxLayout* pulsantiP1 = new QVBoxLayout();
    QToolButton* piuP1 = new QToolButton();
    piuP1->setToolButtonStyle(Qt::ToolButtonTextOnly);
    piuP1->setText("+");
    pulsantiP1->addWidget(piuP1);
    connect(piuP1,SIGNAL(clicked(bool)),this,SLOT(incrementaP1()));
    QToolButton* menoP1 = new QToolButton();
    menoP1->setText("-");
    menoP1->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    pulsantiP1->addWidget(menoP1);
    connect(menoP1,SIGNAL(clicked(bool)),this,SLOT(decrementaP1()));
    punteggio1 = new QLCDNumber();
    punteggio2 = new QLCDNumber();
    QVBoxLayout* pulsantiP2 = new QVBoxLayout();
    QToolButton* piuP2 = new QToolButton();
    piuP2->setText("+");
    pulsantiP2->addWidget(piuP2);
    connect(piuP2,SIGNAL(clicked(bool)),this,SLOT(incrementaP2()));
    QToolButton* menoP2 = new QToolButton();
    menoP2->setText("-");
    menoP2->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    pulsantiP2->addWidget(menoP2);
    connect(menoP2,SIGNAL(clicked(bool)),this,SLOT(decrementaP2()));

    segnaPunti->addLayout(pulsantiP1);
    segnaPunti->addWidget(punteggio1,1);
    segnaPunti->addWidget(punteggio2,1);
    segnaPunti->addLayout(pulsantiP2);

    viewScambio = new QTableView();
    viewScambio->setSelectionMode(QAbstractItemView::SingleSelection);
    viewScambio->setSelectionBehavior(QAbstractItemView::SelectRows);
    viewScambio->setEditTriggers(QAbstractItemView::NoEditTriggers | QAbstractItemView::DoubleClicked);
    modelScambio = new QStandardItemModel();
    viewScambio->setModel(modelScambio);

    QStringList etichette;
    etichette.append("NomeGiocatore");
    etichette.append("Fondamentale");
    etichette.append("Esito");
    modelScambio->setHorizontalHeaderLabels(etichette);
    viewScambio->resizeColumnsToContents();

    addLayout(segnaPunti);
    addWidget(viewScambio);

    QPushButton* rimuoviAzione = new QPushButton("Rimuovi");
    addWidget(rimuoviAzione);

    connect(rimuoviAzione,SIGNAL(clicked(bool)),this,SLOT(rimuoviAzione()));
}

void ScambioCorrente::aggiungiRiga(const QList<QStandardItem*>& prossimoPunto)
{
    modelScambio->appendRow(prossimoPunto);
}

QVector<QVector<QString>> ScambioCorrente::inVector()
{
    QVector<QVector<QString>> vector;
    QVector<QString> riga;
    while (modelScambio->rowCount() != 0)
    {
        riga.append(modelScambio->item(0,0)->text());
        riga.append(modelScambio->item(0,1)->text());
        riga.append(modelScambio->item(0,2)->text());
        modelScambio->removeRow(0);
        vector.append(riga);
        riga.clear();
    }
    return vector;
}

void ScambioCorrente::rimuoviAzione()
{
    if (!viewScambio->selectionModel()->selectedRows().isEmpty())
    {
        modelScambio->removeRow(viewScambio->selectionModel()->selectedRows().first().row());
    }
}

void ScambioCorrente::incrementaP1()
{
    punteggio1->display(punteggio1->intValue()+1);
}

void ScambioCorrente::incrementaP2()
{
    punteggio2->display(punteggio2->intValue()+1);
}

void ScambioCorrente::decrementaP1()
{
    punteggio1->display(punteggio1->intValue()-1);
}

void ScambioCorrente::decrementaP2()
{
    punteggio2->display(punteggio2->intValue()-1);
}
