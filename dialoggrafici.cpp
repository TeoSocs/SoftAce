#include "dialoggrafici.h"
#include "gestoregiocatori.h"
#include <QVBoxLayout>
#include <QtCharts/QBarSet>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QBarCategoryAxis>
#include <QDateTime>
#include <QDir>
#include <QFile>



DialogGrafici::DialogGrafici(GestoreGiocatori* gG) : gestoreGiocatori(gG)
{
    resize(1200,700);
    QVBoxLayout* layout = new QVBoxLayout();
    setLayout(layout);
    selettore = new QComboBox();
    selettore->addItem("Attacco");
    selettore->addItem("Battuta");
    selettore->addItem("Ricezione");
    layout->addWidget(selettore);
    stack = new QStackedWidget();
    layout->addWidget(stack);

    // COSTRUZIONE GRAFICI
    QString titoloGrafico;
    for (int i=0;i<selettore->count();i++)
    {
        titoloGrafico = selettore->itemText(i);
        QChart* chart = new QChart();
        chart->createDefaultAxes();
        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);
        chart->setTitle(titoloGrafico);
        QFont titleFont = chart->titleFont();
        titleFont.setPixelSize(35);
        QFont font;
        font.setPixelSize(20);
        font.setWeight(QFont::DemiBold);
        chart->setTitleFont(font);
        QChartView* chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
        chartView->resize(1200,700);
        stack->addWidget(chartView);
        Chart[titoloGrafico] = chart;
        ChartView[titoloGrafico] = chartView;
    }
    connect(selettore,SIGNAL(currentIndexChanged(QString)),this,SLOT(selectionChanged()));
}

void DialogGrafici::aggiornaGrafico(QString titolo)
{
    Chart[titolo]->removeAllSeries();
    if (titolo == "Attacco" || titolo == "Battuta" || titolo == "Ricezione")
    {
        QStringList nomi;
        QBarSet* DoppioMeno = new QBarSet("=");
        DoppioMeno->setColor(/*Qt::red*/QColor(192,0,0));
        QBarSet* Meno = new QBarSet("-");
        Meno->setColor(/*Qt::yellow*/QColor(255,255,0));
        QBarSet* Piu = new QBarSet("+");
        Piu->setColor(/*Qt::green*/QColor(0,176,80));
        QBarSet* DoppioPiu = new QBarSet("#");
        DoppioPiu->setColor(/*Qt::cyan*/QColor(0,32,96));
        bool graficonullo = true;
        int offset = 0;
        if (titolo == "Battuta") offset = 1;
        else if (titolo == "Ricezione") offset = 6;
        else if (titolo == "Attacco") offset = 11;
        for (int i=0;i<gestoreGiocatori->modelGiocatori->rowCount();i++)
        {
            if (gestoreGiocatori->modelGiocatori->item(i,offset+4)->text().toInt() != 0 ||
                    gestoreGiocatori->modelGiocatori->item(i,offset+3)->text().toInt() != 0 ||
                    gestoreGiocatori->modelGiocatori->item(i,offset+2)->text().toInt() != 0 ||
                    gestoreGiocatori->modelGiocatori->item(i,offset+1)->text().toInt() != 0)
            {
                graficonullo = false;
            }
            nomi << gestoreGiocatori->modelGiocatori->item(i)->text();
            *DoppioMeno << gestoreGiocatori->modelGiocatori->item(i,offset+1)->text().toInt();
            *Meno << gestoreGiocatori->modelGiocatori->item(i,offset+2)->text().toInt();
            *Piu << gestoreGiocatori->modelGiocatori->item(i,offset+3)->text().toInt();
            *DoppioPiu << gestoreGiocatori->modelGiocatori->item(i,offset+4)->text().toInt();
        }
        QStackedBarSeries* serie = new QStackedBarSeries();
        qreal barWidth = serie->barWidth();
        barWidth *= 0.5;
        serie->setBarWidth(barWidth);
        serie->append(DoppioMeno);
        serie->append(Meno);
        serie->append(Piu);
        serie->append(DoppioPiu);
        if (!graficonullo)
        {
            Chart[titolo]->addSeries(serie);
        }
        QBarCategoryAxis* axis = new QBarCategoryAxis();
        axis->append(nomi);
        QFont font = axis->labelsFont();
        font.setPixelSize(16);
        axis->setLabelsFont(font);
        Chart[titolo]->setAxisX(axis);
    }
}

void DialogGrafici::updateAndShow()
{
    for (int i=0;i<selettore->count();i++)
    {
        aggiornaGrafico(selettore->itemText(i));
        show();
    }
}

void DialogGrafici::selectionChanged()
{
    aggiornaGrafico(selettore->currentText());
    stack->setCurrentIndex(selettore->currentIndex());
}

void DialogGrafici::esportaGraficiJPG()
{
    if (!QDir(QDir::currentPath()+ "\\Esportati\\").exists())
    {
        QDir::current().mkdir("Esportati");
    }
    if (!QDir(QDir::currentPath()+"\\Esportati\\JPG\\").exists())
    {
        QDir(QDir::currentPath()+"\\Esportati\\").mkdir("JPG");
    }
    QString nomefile;
    for (int i=0;i<selettore->count();i++)
    {
        selettore->setCurrentIndex(i);
        aggiornaGrafico(selettore->currentText());
        stack->setCurrentIndex(i);
        nomefile = QDir::currentPath() + "\\Esportati\\JPG\\";
        nomefile += QDateTime::currentDateTime().toLocalTime().toString("yy-MM-dd HH.mm ");
        nomefile += selettore->currentText();
        nomefile += ".jpg";
        stack->currentWidget()->grab().save(nomefile,"JPG");
    }
    selettore->setCurrentIndex(0);
}
