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

void BackgroundMethods::Calculations(Abnormal_Payment_Node *_Head, double _Mortgage_Amount, double _Interest, double _Normal_monthly_rate)
{
    //Gets time
    time_t CurrTimeInSec = time(0);
    tm *TempCurTime= localtime(&CurrTimeInSec);
    TempCurTime->tm_year += 1900;
    TempCurTime->tm_mon += 1;
    QDateTime CurTime;
    CurTime.setDate(QDate(TempCurTime->tm_year, TempCurTime->tm_mon, 1));


    //count how many points
    double _current_Mortage_Amount = _Mortgage_Amount;

    QFile DataPoints(QCoreApplication::applicationDirPath() + "/DataPoints.txt");
    if (!DataPoints.open(QIODevice::WriteOnly)) {
        return;
    }

    QTextStream WriteStream(&DataPoints);


    QDateTime _Time = CurTime;
    Abnormal_Payment_Node *_node_Temp = _Head;

    WriteStream << "# Year Month Mortgage Amount" << endl;
    WriteStream << _Time.toString("yyyy M") <<  " " << _current_Mortage_Amount << endl;

    while(_current_Mortage_Amount >= 0){
        while(_node_Temp != NULL && _Time >= _node_Temp->Time){
            if(_Time == _node_Temp->Time){
                _current_Mortage_Amount -= _node_Temp->Amount;
            }
            _node_Temp = _node_Temp->next;
        }
        _current_Mortage_Amount -= _Normal_monthly_rate;
        _current_Mortage_Amount += (_current_Mortage_Amount * (_Interest/100 / 12));

        _Time = _Time.addMonths(1);
        if(_current_Mortage_Amount > 0){
            WriteStream << _Time.toString("yyyy MM") <<  " " << _current_Mortage_Amount << endl;
        }else{
            WriteStream << _Time.toString("yyyy MM") <<  " " << 0.00 << endl;
        }
    }
    DataPoints.close();
    return;
}
