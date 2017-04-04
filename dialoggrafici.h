#ifndef DIALOGGRAFICI_H
#define DIALOGGRAFICI_H

#include <QDialog>
#include <QStackedWidget>
#include <QComboBox>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>



QT_CHARTS_USE_NAMESPACE


class GestoreGiocatori;

class DialogGrafici : public QDialog
{
    Q_OBJECT

public:
    explicit DialogGrafici(GestoreGiocatori*);
    void esportaGraficiJPG();

public slots:
    void updateAndShow();
    void selectionChanged();

private:
    void aggiornaGrafico(QString);
    GestoreGiocatori* gestoreGiocatori;
    QStackedWidget* stack;
    QComboBox* selettore;
    QMap<QString,QChart*> Chart;
    QMap<QString,QChartView*> ChartView;
};

#endif // DIALOGGRAFICI_H
