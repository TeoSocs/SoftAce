#ifndef PULSANTIERA_H
#define PULSANTIERA_H

#include <QVBoxLayout>
#include <QStandardItem>

class ScambioCorrente;
class GestoreGiocatori;


class Pulsantiera : public QVBoxLayout
{
    Q_OBJECT

public:
    explicit Pulsantiera(ScambioCorrente*,GestoreGiocatori*);

private:
    ScambioCorrente* scambioCorrente;
    GestoreGiocatori* gestoreGiocatori;
    QList<QStandardItem*> prossimoPunto;

private slots:
    void clickBat();
    void clickRic();
    void clickAtt();
    void clickMur();
    void clickPiu();
    void clickDoppioPiu();
    void clickMeno();
    void clickDoppioMeno();
    void clickP1();
    void clickP2();
};

#endif // PULSANTIERA_H
