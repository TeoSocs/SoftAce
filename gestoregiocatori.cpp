#include "gestoregiocatori.h"
#include "dialoggrafici.h"

#include <QTableView>
#include <QHBoxLayout>
#include <QPushButton>
#include <QStandardItemModel>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QDateTime>
#include <QDesktopServices>

GestoreGiocatori::GestoreGiocatori()
{
    // TABLE GIOCATORI

    viewGiocatori = new QTableView();
    viewGiocatori->setSelectionMode(QAbstractItemView::SingleSelection);
    viewGiocatori->setSelectionBehavior(QAbstractItemView::SelectRows);
    viewGiocatori->setEditTriggers(QAbstractItemView::NoEditTriggers | QAbstractItemView::DoubleClicked);
    modelGiocatori = new QStandardItemModel();
    viewGiocatori->setModel(modelGiocatori);
    dialogGrafici = new DialogGrafici(this);

    connect(modelGiocatori,SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),this,SLOT(aggiornaTotali()));

    QStringList etichette;
        etichette.append("Nome giocatore");
        etichette.append("BAT tot");
        etichette.append("BAT =");
        etichette.append("BAT -");
        etichette.append("BAT +");
        etichette.append("BAT #");
        etichette.append("RIC tot");
        etichette.append("RIC =");
        etichette.append("RIC -");
        etichette.append("RIC +");
        etichette.append("RIC #");
        etichette.append("ATT tot");
        etichette.append("ATT =");
        etichette.append("ATT -");
        etichette.append("ATT +");
        etichette.append("ATT #");
        etichette.append("MUR =");
        etichette.append("MUR #");
        modelGiocatori->setHorizontalHeaderLabels(etichette);
        viewGiocatori->resizeColumnsToContents();


    // PULSANTI GIOCATORI

    QHBoxLayout* pulsantiGiocatori = new QHBoxLayout();
    QPushButton* aggiungiGiocatore = new QPushButton("Aggiungi");
    QPushButton* eliminaGiocatore = new QPushButton("Elimina");
    QPushButton* mostraGrafici = new QPushButton("&Grafici");

    pulsantiGiocatori->addWidget(aggiungiGiocatore);
    pulsantiGiocatori->addWidget(eliminaGiocatore);
    pulsantiGiocatori->addWidget(mostraGrafici);

    connect(aggiungiGiocatore,SIGNAL(clicked(bool)),this,SLOT(aggiungiGiocatore()));
    connect(eliminaGiocatore,SIGNAL(clicked(bool)),this,SLOT(eliminaGiocatore()));
    connect(mostraGrafici,SIGNAL(clicked(bool)),dialogGrafici,SLOT(updateAndShow()));


    addWidget(viewGiocatori);
    addLayout(pulsantiGiocatori);
}

void GestoreGiocatori::caricaPreset()
{
    QFile preset(QDir::currentPath() + "\\Preset\\Squadra.txt");
        if (preset.open(QIODevice::ReadOnly))
        {
            QTextStream in(&preset);
            QString nome;
            QList<QStandardItem*> giocatore;
            while (!in.atEnd())
            {
                nome = in.readLine();
                giocatore.append(new QStandardItem(nome));
                for (int i=0;i<17;i++)
                {
                    giocatore.append(new QStandardItem(QString(QString::number(0))));
                }
                modelGiocatori->appendRow(giocatore);
                giocatore.clear();
            }
            preset.close();
        }
}

void GestoreGiocatori::modificaPreset()
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(QDir::currentPath()+"\\Preset\\"));
}

void GestoreGiocatori::aggiungiGiocatore()
{
    QList<QStandardItem*> giocatore;
    giocatore.append(new QStandardItem("Nuovo Giocatore"));
    for (int i=0;i<17;i++)
    {
        giocatore.append(new QStandardItem(QString(QString::number(0))));
    }
    modelGiocatori->appendRow(giocatore);
}

void GestoreGiocatori::eliminaGiocatore()
{
    if (!viewGiocatori->selectionModel()->selectedRows().isEmpty())
    {
        modelGiocatori->removeRow(viewGiocatori->selectionModel()->selectedRows().first().row());
    }
}

QString GestoreGiocatori::getSelectedPlayer() const
{
    if (!viewGiocatori->selectionModel()->selectedRows().isEmpty())
    {
        QModelIndex selected = viewGiocatori->selectionModel()->selectedRows().first();
        QStandardItem* item = modelGiocatori->itemFromIndex(selected);
        return item->text();
    }
    return "";
}

void GestoreGiocatori::aggiungiDato(QVector<QString> azione)
{
    int riga;
    int fondamentale = 0;
    int esito = 0;
    QList<QStandardItem*> giocatore = modelGiocatori->findItems(azione[0]);


    if (azione[1] == "Battuta") fondamentale = 1;
    else if (azione[1] == "Ricezione") fondamentale = 6;
    else if (azione[1] == "Attacco") fondamentale = 11;
    else if (azione[1] == "Muro")
    {
        if (azione[2] == "=")
        {
            if (!giocatore.isEmpty())
            {
                riga = giocatore.first()->row();
                int numeroPrecedente = modelGiocatori->item(riga,16)->text().toInt();
                numeroPrecedente++;
                modelGiocatori->item(riga,16)->setText(QString::number(numeroPrecedente));
            }
            return;
        }
        if (azione[2] == "#")
        {
            if (!giocatore.isEmpty())
            {
                riga = giocatore.first()->row();
                int numeroPrecedente = modelGiocatori->item(riga,17)->text().toInt();
                numeroPrecedente++;
                modelGiocatori->item(riga,17)->setText(QString::number(numeroPrecedente));
            }
            return;
        }
    }


    if (azione[2] == "=") esito = 1;
    else if (azione[2] == "-") esito = 2;
    else if (azione[2] == "+") esito = 3;
    else if (azione[2] == "#") esito = 4;


    if (fondamentale != 0 && esito != 0 && !giocatore.isEmpty())
    {
        riga = giocatore.first()->row();
        int colonna = fondamentale + esito;
        int numeroPrecedente = modelGiocatori->item(riga,colonna)->text().toInt();
        numeroPrecedente++;
        modelGiocatori->item(riga,colonna)->setText(QString::number(numeroPrecedente));
    }
}

void GestoreGiocatori::esportaTabella()
{
    QString textData = "";
    int rows = modelGiocatori->rowCount();
    int columns = modelGiocatori->columnCount();
    for (int i = 0; i < columns; i++)
    {
        textData += modelGiocatori->headerData(i, Qt::Horizontal).toString();
        textData += ", ";
    }
    textData += "\n";
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            textData += modelGiocatori->itemFromIndex(modelGiocatori->index(i,j))->text();
            textData += ", ";
        }
        textData += "\n";
    }
    if (!QDir(QDir::currentPath()+ "\\Esportati\\").exists())
    {
        QDir::current().mkdir("Esportati");
    }
    QString nomefile = QDir::currentPath() + "\\Esportati\\" + QDateTime::currentDateTime().toLocalTime().toString("yy-MM-dd HH.mm ") + ".csv";
    QFile csvFile(nomefile);
    if(csvFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        QTextStream out(&csvFile);
        out << "sep=,\n";
        out << textData;
        csvFile.close();
    }
    QDesktopServices::openUrl(QUrl::fromLocalFile(QDir::currentPath()+"\\Esportati\\"));
}

void GestoreGiocatori::esportaGrafici()
{
    dialogGrafici->esportaGraficiJPG();
}

void GestoreGiocatori::aggiornaTotali()
{
    if (modelGiocatori->rowCount() == 0) return;
    int sum = 0;
    for (int x = 0; x < modelGiocatori->rowCount(); x++)
    {
        int y = 1;
        while (y < 12)
        {
            for (int i = 1; i < 5; i++)
            {
                sum += modelGiocatori->item(x,y+i)->text().toInt();
            }
            modelGiocatori->item(x,y)->setText(QString::number(sum));
            sum = 0;
            y += 5;
        }
    }
}



















