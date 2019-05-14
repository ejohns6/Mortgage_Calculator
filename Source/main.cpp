/*
#include "mainwindow.h"
#include "mortgage_graph.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    //QApplication a(argc, argv);
    //MainWindow MainWindow;
    //MainWindow.show();
    _Graph(argc, argv);
    //_Graph();

    return 0;
    //return a.exec();
}
*/

#include "mainwindow.h"
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

QT_CHARTS_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication _a(argc, argv);


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

    BackgroundMethods::M_Amortization_Calculations(Head, Mortgage_Amount, Yearly_Interest_Rate, Normal_Monthly_Payment);

    //Starts of Modified Balance
    QFile M_Balance_DataPoints(QCoreApplication::applicationDirPath() + "/M_Balance_DataPoints.txt");
    if (!M_Balance_DataPoints.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return 1;
    }


    QLineSeries *M_Balance_Series = new QLineSeries();
    M_Balance_Series->setName("Balance");
    QTextStream M_Balance_streamPoints(&M_Balance_DataPoints);
    while (!M_Balance_streamPoints.atEnd()) {
        QString line = M_Balance_streamPoints.readLine();
        if (line.startsWith("#")){
            continue;
        }
        QStringList values = line.split(" ", QString::SkipEmptyParts);
        QDateTime momentInTime;
        momentInTime.setDate(QDate(values[0].toInt(), values[1].toInt() , 1));
        M_Balance_Series->append(momentInTime.toMSecsSinceEpoch(), values[2].toDouble());
    }
    M_Balance_DataPoints.close();
    //End of Modified Balance

    //Starts of Modified Cumulative Interest
    QFile M_Cumulative_Interest_DataPoints(QCoreApplication::applicationDirPath() + "/M_Cumulative_Interest_DataPoints.txt");
    if (!M_Cumulative_Interest_DataPoints.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return 1;
    }


    QLineSeries *M_Cumulative_Interest_Series = new QLineSeries();
    M_Cumulative_Interest_Series->setName("Cumulative Interest");
    QTextStream M_Cumulative_Interest_streamPoints(&M_Cumulative_Interest_DataPoints);
    while (!M_Cumulative_Interest_streamPoints.atEnd()) {
        QString line = M_Cumulative_Interest_streamPoints.readLine();
        if (line.startsWith("#")){
            continue;
        }
        QStringList values = line.split(" ", QString::SkipEmptyParts);
        QDateTime momentInTime;
        momentInTime.setDate(QDate(values[0].toInt(), values[1].toInt() , 1));
        M_Cumulative_Interest_Series->append(momentInTime.toMSecsSinceEpoch(), values[2].toDouble());
    }
    M_Cumulative_Interest_DataPoints.close();
    //End of Modified Cumulative Interest

    //Starts of Modified Principal Paid
    QFile M_Principal_Paid_DataPoints(QCoreApplication::applicationDirPath() + "/M_Principal_Paid_DataPoints.txt");
    if (!M_Principal_Paid_DataPoints.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return 1;
    }


    QLineSeries *M_Principal_Paid_Series = new QLineSeries();
    M_Principal_Paid_Series->setName("Principal Paid");
    QTextStream M_Principal_Paid_streamPoints(&M_Principal_Paid_DataPoints);
    while (!M_Principal_Paid_streamPoints.atEnd()) {
        QString line = M_Principal_Paid_streamPoints.readLine();
        if (line.startsWith("#")){
            continue;
        }
        QStringList values = line.split(" ", QString::SkipEmptyParts);
        QDateTime momentInTime;
        momentInTime.setDate(QDate(values[0].toInt(), values[1].toInt() , 1));
        M_Principal_Paid_Series->append(momentInTime.toMSecsSinceEpoch(), values[2].toDouble());
    }
    M_Principal_Paid_DataPoints.close();
    //End of Modified Principal Paid

    //![2]

    //![3]
    QChart *chart = new QChart();
    chart->addSeries(M_Balance_Series);
    chart->addSeries(M_Cumulative_Interest_Series);
    chart->addSeries(M_Principal_Paid_Series);
    //chart->legend()->hide();
    chart->setTitle("Mortgage Amount Over Time");
    //![3]

    //![4]
    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setTickCount(10);
    axisX->setFormat("MMM yyyy");
    axisX->setTitleText("Date");
    chart->addAxis(axisX, Qt::AlignBottom);
    M_Balance_Series->attachAxis(axisX);
    M_Cumulative_Interest_Series->attachAxis(axisX);
    M_Principal_Paid_Series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis;
    axisY->setLabelFormat("%i");
    axisY->setTitleText("Money Amount($)");
    chart->addAxis(axisY, Qt::AlignLeft);
    M_Balance_Series->attachAxis(axisY);
    M_Cumulative_Interest_Series->attachAxis(axisY);
    M_Principal_Paid_Series->attachAxis(axisY);

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
