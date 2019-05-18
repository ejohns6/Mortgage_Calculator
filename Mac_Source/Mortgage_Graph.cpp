#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCore/QDateTime>
#include <QtCharts/QDateTimeAxis>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QDebug>
#include <QtCharts/QValueAxis>

#include "backgroundmethods.h"
#include "mortgage_graph.h"

QT_CHARTS_USE_NAMESPACE

int _Graph(int argc, char *argv[])
{
    QApplication _a(argc, argv);
    QLineSeries *series = new QLineSeries();

    //Get the info in
    QFile InputData(QCoreApplication::applicationDirPath() + "/InputData.txt");
    QString fEmp = QCoreApplication::applicationDirPath();
    qDebug() << "File Path: " << fEmp;
    if(!InputData.exists()){
        return 1;

    }

    if (!InputData.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return 1;
    }

    QTextStream streamI(&InputData);

    double Mortgage_Amount = 0;
    double Yearly_Interest_Rate = 0;
    double Normal_Monthly_Payment = 0;

    Abnormal_Payment_Node *Head = new Abnormal_Payment_Node;

    while (!streamI.atEnd()) {
        QString line = streamI.readLine();
        if(line.startsWith("# Mortgage Amount($):")){
            QString line = streamI.readLine();
            Mortgage_Amount = line.toDouble();
            continue;
        }else if (line.startsWith("# Yearly Interest Rate(%):")){
            QString line = streamI.readLine();
            Yearly_Interest_Rate = line.toDouble();
            continue;
        }else if (line.startsWith("# Normal Monthly Payment:")){
            QString line = streamI.readLine();
            Normal_Monthly_Payment = line.toDouble();
            continue;
        }else if (line.startsWith("#")){
            continue;
        }

        QStringList values = line.split(" ", QString::SkipEmptyParts);
        QDateTime momentInTime;
        momentInTime.setDate(QDate(values[0].toInt(), values[1].toInt() , 1));
        Abnormal_Payment_Node  *temp_Abnormal_Payment_Node = new Abnormal_Payment_Node;
        temp_Abnormal_Payment_Node->Time = momentInTime;
        temp_Abnormal_Payment_Node->Amount = values[2].toDouble();
        temp_Abnormal_Payment_Node->inUse = true;
        Abnormal_Payment_Node::Insert_Abnormal_pay_Node(&Head, temp_Abnormal_Payment_Node);
    }
    InputData.close();

    BackgroundMethods::Calculations(Head, Mortgage_Amount, Yearly_Interest_Rate, Normal_Monthly_Payment);


    QFile DataPoints("DataPoints.txt");
    if (!InputData.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return 1;
    }

    QTextStream streamPoints(&DataPoints);
    while (!streamPoints.atEnd()) {
        QString line = streamPoints.readLine();
        if (line.startsWith("#")){
            continue;
        }
        QStringList values = line.split(" ", QString::SkipEmptyParts);
        QDateTime momentInTime;
        momentInTime.setDate(QDate(values[0].toInt(), values[1].toInt() , 0));
        series->append(momentInTime.toMSecsSinceEpoch(), values[2].toDouble());
    }
    InputData.close();

    //![2]

    //![3]
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->legend()->hide();
    chart->setTitle("Mortgage Amount Over Time");
    //![3]

    //![4]
    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setTickCount(10);
    axisX->setFormat("MMM yyyy");
    axisX->setTitleText("Date");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis;
    axisY->setLabelFormat("%i");
    axisY->setTitleText("Mortgage Amount($)");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    //![4]

    //![5]
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    //![5]

    //![6]
    QMainWindow window;
    window.setCentralWidget(chartView);
    window.resize(820, 600);
    window.show();
    //![6]

    return _a.exec();
}
