#include <iostream>
#include <ctime>
#include <QtCore/QDateTime>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtWidgets/QApplication>


using namespace std;

#include "abnormal_payment_node.h"
#include "backgroundmethods.h"

//void delete(Abnormal_pay_Node *Head)

void BackgroundMethods::M_Amortization_Calculations(Abnormal_Payment_Node *_Head, double _Mortgage_Amount, double _Interest, double _Normal_monthly_rate)
{
    //Gets time
    time_t CurrTimeInSec = time(0);
    tm *TempCurTime= localtime(&CurrTimeInSec);
    TempCurTime->tm_year += 1900;
    TempCurTime->tm_mon += 1;
    QDateTime CurTime;
    CurTime.setDate(QDate(TempCurTime->tm_year, TempCurTime->tm_mon, 1));




    //Start: Opens M_Balance_DataPoints
    double _current_Mortage_Amount = _Mortgage_Amount;

    QFile M_Balance_DataPoints(QCoreApplication::applicationDirPath() + "/M_Balance_DataPoints.txt");
    if (!M_Balance_DataPoints.open(QIODevice::WriteOnly)) {
        return;
    }

    QTextStream M_Balance_WriteStream(&M_Balance_DataPoints);

    QDateTime _Time = CurTime;
    Abnormal_Payment_Node *_node_Temp = _Head;


    M_Balance_WriteStream << "# Year Month Mortgage Amount" << endl;
    M_Balance_WriteStream << _Time.toString("yyyy M") <<  " " << _current_Mortage_Amount << endl;
    //End: Opens M_Balance_DataPoints


    //Start: Opens M_Cumulative_Interest_DataPoints
    double _Cumulative_Interest_Amount = 0.00;

    QFile M_Cumulative_Interest_DataPoints(QCoreApplication::applicationDirPath() + "/M_Cumulative_Interest_DataPoints.txt");
    if (!M_Cumulative_Interest_DataPoints.open(QIODevice::WriteOnly)) {
        return;
    }

    QTextStream M_Cumulative_Interest_WriteStream(&M_Cumulative_Interest_DataPoints);

    M_Cumulative_Interest_WriteStream << "# Year Month Cumulative Interest Amount" << endl;
    M_Cumulative_Interest_WriteStream << _Time.toString("yyyy M") <<  " " << _Cumulative_Interest_Amount << endl;
    //End: Opens M_Cumulative_Interest_DataPoints


    //Start: Opens M_Principal_Paid_DataPoints
    double _Principal_Paid_Amount = 0.00;

    QFile M_Principal_Paid_DataPoints(QCoreApplication::applicationDirPath() + "/M_Principal_Paid_DataPoints.txt");
    if (!M_Principal_Paid_DataPoints.open(QIODevice::WriteOnly)) {
        return;
    }

    QTextStream M_Principal_Paid_WriteStream(&M_Principal_Paid_DataPoints);

    M_Principal_Paid_WriteStream << "# Year Month Principal Paid Amount" << endl;
    M_Principal_Paid_WriteStream << _Time.toString("yyyy M") <<  " " << _Principal_Paid_Amount << endl;
    //End: Opens M_Principal_Paid_DataPoints


    while(_current_Mortage_Amount >= 0){
        double _Temp_Principal_Paid_Amount = 0.00;
        while(_node_Temp != NULL && _Time >= _node_Temp->Time){
            if(_Time == _node_Temp->Time){
                _current_Mortage_Amount -= _node_Temp->Amount;
                _Temp_Principal_Paid_Amount += _node_Temp->Amount;
            }
            _node_Temp = _node_Temp->next;
        }
        _current_Mortage_Amount -= _Normal_monthly_rate;
        _current_Mortage_Amount += (_current_Mortage_Amount * (_Interest/100 / 12));

        _Cumulative_Interest_Amount += (_current_Mortage_Amount * (_Interest/100 / 12));

        _Principal_Paid_Amount += _Temp_Principal_Paid_Amount + _Normal_monthly_rate - (_current_Mortage_Amount * (_Interest/100 / 12));

        _Time = _Time.addMonths(1);
        if(_current_Mortage_Amount > 0){
            M_Balance_WriteStream << _Time.toString("yyyy MM") <<  " " << _current_Mortage_Amount << endl;

            M_Cumulative_Interest_WriteStream << _Time.toString("yyyy MM") <<  " " << _Cumulative_Interest_Amount << endl;

            M_Principal_Paid_WriteStream << _Time.toString("yyyy MM") <<  " " << _Principal_Paid_Amount << endl;
        }else{
            M_Balance_WriteStream << _Time.toString("yyyy MM") <<  " " << 0.00 << endl;

            M_Cumulative_Interest_WriteStream << _Time.toString("yyyy MM") <<  " " << _Cumulative_Interest_Amount << endl;

            M_Principal_Paid_WriteStream << _Time.toString("yyyy MM") <<  " " << _Mortgage_Amount << endl;
        }
    }
    M_Balance_DataPoints.close();
    return;
}
