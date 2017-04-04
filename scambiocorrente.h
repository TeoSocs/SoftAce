#ifndef SCAMBIOCORRENTE_H
#define SCAMBIOCORRENTE_H

#include <QVBoxLayout>
#include <QLCDNumber>
#include <QTableView>
#include <QVector>
#include <QString>
#include <QStandardItem>

class ScambioCorrente : public QVBoxLayout
{
    Q_OBJECT

public:
    explicit ScambioCorrente();
    void aggiungiRiga(const QList<QStandardItem*>&);
    QVector<QVector<QString>> inVector();

public slots:
    void incrementaP1();
    void incrementaP2();
    void decrementaP1();
    void decrementaP2();
    void rimuoviAzione();

private:
    QLCDNumber* punteggio1;
    QLCDNumber* punteggio2;
    QTableView* viewScambio;
    QStandardItemModel* modelScambio;
};

#endif // SCAMBIOCORRENTE_H
