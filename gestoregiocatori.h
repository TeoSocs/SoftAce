#ifndef GESTOREGIOCATORI_H
#define GESTOREGIOCATORI_H

#include <QVBoxLayout>
#include <QStandardItemModel>
#include <QTableView>
#include <QString>


class DialogGrafici;

class GestoreGiocatori : public QVBoxLayout
{
    Q_OBJECT

    friend class DialogGrafici;

public:
    explicit GestoreGiocatori();
    QString getSelectedPlayer() const;
    void aggiungiDato(QVector<QString>);

public slots:
    void caricaPreset();
    void modificaPreset();
    void esportaTabella();
    void esportaGrafici();

private:
    QStandardItemModel* modelGiocatori;
    QTableView* viewGiocatori;
    DialogGrafici* dialogGrafici;

private slots:
    void aggiungiGiocatore();
    void eliminaGiocatore();
    void aggiornaTotali();
};

#endif // GESTOREGIOCATORI_H
