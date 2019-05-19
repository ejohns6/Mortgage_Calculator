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

#include <QBoxLayout>

#include "backgroundmethods.h"

QT_CHARTS_USE_NAMESPACE

QLineSeries* makeLineSeries(T_and_D_Node* Head, QString SeriesName){

    QLineSeries *Series = new QLineSeries();

    T_and_D_Node* current = Head;
    while(current->getNext() != NULL){

        QStringList values = current->getDate().split(" ", QString::SkipEmptyParts);
        QDateTime momentInTime;
        momentInTime.setDate(QDate(values[0].toInt(), values[1].toInt() , 1));
        Series->append(momentInTime.toMSecsSinceEpoch(), current->getAmount());
        current = current->getNext();
    }
    QStringList values = current->getDate().split(" ", QString::SkipEmptyParts);
    QDateTime momentInTime;
    momentInTime.setDate(QDate(values[0].toInt(), values[1].toInt() , 1));
    Series->append(momentInTime.toMSecsSinceEpoch(), current->getAmount());
    Series->setName(SeriesName + ": $" + QString::number(current->getAmount()));
    return(Series);
}

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

    //Start: Modified Amortization Calculations and Creating Graphs
    Time_And_Date_Table* M_Data_Table = BackgroundMethods::M_Amortization_Calculations(Head, Mortgage_Amount, Yearly_Interest_Rate, Normal_Monthly_Payment);

    QLineSeries *M_Balance_Series = makeLineSeries(M_Data_Table->Balance_getHead(), "Balance");

    QLineSeries *M_Cumulative_Interest_Series = makeLineSeries(M_Data_Table->Cum_Interest_getHead(), "Cumulative Interest");

    QLineSeries *M_Principal_Paid_Series = makeLineSeries(M_Data_Table->Principal_Paid_getHead(), "Principal Paid");

    QChart *M_chart = new QChart();
    M_chart->addSeries(M_Balance_Series);
    M_chart->addSeries(M_Cumulative_Interest_Series);
    M_chart->addSeries(M_Principal_Paid_Series);
    M_chart->legend()->setVisible(true);
    M_chart->legend()->setAlignment(Qt::AlignBottom);
    M_chart->setTitle("Modified Mortgage Amount Over Time");

    QDateTimeAxis *M_axisX = new QDateTimeAxis;
    M_axisX->setTickCount(10);
    M_axisX->setFormat("MMM yyyy");
    M_axisX->setTitleText("Date");
    M_chart->addAxis(M_axisX, Qt::AlignBottom);
    M_Balance_Series->attachAxis(M_axisX);
    M_Cumulative_Interest_Series->attachAxis(M_axisX);
    M_Principal_Paid_Series->attachAxis(M_axisX);

    QValueAxis *M_axisY = new QValueAxis;
    M_axisY->setLabelFormat("%i");
    M_axisY->setTitleText("Money Amount($)");
    M_chart->addAxis(M_axisY, Qt::AlignLeft);
    M_Balance_Series->attachAxis(M_axisY);
    M_Cumulative_Interest_Series->attachAxis(M_axisY);
    M_Principal_Paid_Series->attachAxis(M_axisY);


    QChartView *M_chartView = new QChartView(M_chart);
    M_chartView->setRenderHint(QPainter::Antialiasing);
    //End: Modified Amortization Calculations and Creating Graphs

    //Start: Non-Modified Amortization Calculations and Creating Graphs
    Time_And_Date_Table* NM_Data_Table = BackgroundMethods::NM_Amortization_Calculations(Mortgage_Amount, Yearly_Interest_Rate, Normal_Monthly_Payment);


    QLineSeries *NM_Balance_Series = makeLineSeries(NM_Data_Table->Balance_getHead(), "Balance");

    QLineSeries *NM_Cumulative_Interest_Series = makeLineSeries(NM_Data_Table->Cum_Interest_getHead(), "Cumulative Interest");

    QLineSeries *NM_Principal_Paid_Series = makeLineSeries(NM_Data_Table->Principal_Paid_getHead(), "Principal Paid");


    QChart *NM_chart = new QChart();
    NM_chart->addSeries(NM_Balance_Series);
    NM_chart->addSeries(NM_Cumulative_Interest_Series);
    NM_chart->addSeries(NM_Principal_Paid_Series);
    NM_chart->legend()->setVisible(true);
    NM_chart->legend()->setAlignment(Qt::AlignBottom);
    NM_chart->setTitle("Non-Modified Mortgage Amount Over Time");

    QDateTimeAxis *NM_axisX = new QDateTimeAxis;
    NM_axisX->setTickCount(10);
    NM_axisX->setFormat("MMM yyyy");
    NM_axisX->setTitleText("Date");
    NM_chart->addAxis(NM_axisX, Qt::AlignBottom);
    NM_Balance_Series->attachAxis(NM_axisX);
    NM_Cumulative_Interest_Series->attachAxis(NM_axisX);
    NM_Principal_Paid_Series->attachAxis(NM_axisX);

    QValueAxis *NM_axisY = new QValueAxis;
    NM_axisY->setLabelFormat("%i");
    NM_axisY->setTitleText("Money Amount($)");
    NM_chart->addAxis(NM_axisY, Qt::AlignLeft);
    NM_Balance_Series->attachAxis(NM_axisY);
    NM_Cumulative_Interest_Series->attachAxis(NM_axisY);
    NM_Principal_Paid_Series->attachAxis(NM_axisY);


    QChartView *NM_chartView = new QChartView(NM_chart);
    NM_chartView->setRenderHint(QPainter::Antialiasing);
    //End: Non-Modified Amortization Calculations and Creating Graphs


    //![6]
    QWidget *window = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(M_chartView);
    layout->addWidget(NM_chartView);
    window->setLayout(layout);
    window->resize(1620,800);
    window->show();
    /*
    QMainWindow window;
    window.setCentralWidget(M_chartView);
    window.resize(820, 600);
    window.show();
    //![6]
    */

    return _a.exec();
}
