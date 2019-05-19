#include <iostream>
#include <ctime>
#include <QtCore/QDateTime>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtWidgets/QApplication>

#include "time_and_date_table.h"

using namespace std;

#include "abnormal_payment_node.h"
#include "backgroundmethods.h"

double BackgroundMethods::interestRateCalculation(QDateTime _Time, double _Interest){
    bool LeapYear;

    //Convert QDateTime to QString to int
    int _Year = _Time.toString("yyyy").split(" ")[0].toInt();
    if((_Year%4 == 0 && _Year%100 == 0 && _Year%400 == 0) && (_Year%4 == 0 && _Year%100 != 100)){
        LeapYear = true;
    }else{
        LeapYear = false;
    }

    int _Month = _Time.toString("MM").split(" ")[0].toInt();
    if(LeapYear){
        //Days with 31 Days
        if(_Month == 1 || _Month == 3 || _Month == 5 || _Month == 7 || _Month == 8 || _Month == 10 || _Month == 12){
            return((_Interest/100.00) * (31/366.00));
        }
        //Days with 30 Days
        else if(_Month == 4 || _Month == 6 || _Month == 9 || _Month == 11){
            return((_Interest/100.00) * (30/366.00));
        }
        //If Feb thus 29
        else{
            return((_Interest/100.00) * (29/366.00));
        }
    }else{
        //Days with 31 Days
        if(_Month == 1 || _Month == 3 || _Month == 5 || _Month == 7 || _Month == 8 || _Month == 10 || _Month == 12){
            return((_Interest/100.00) * (31.00/365.00));
        }
        //Days with 30 Days
        else if(_Month == 4 || _Month == 6 || _Month == 9 || _Month == 11){
            return((_Interest/100.00) * (30.00/365.00));
        }
        //If Feb thus 28
        else{
            return((_Interest/100) * (28.00/365));
        }
    }


}

Time_And_Date_Table* BackgroundMethods::M_Amortization_Calculations(Abnormal_Payment_Node *_Head, double _Mortgage_Amount, double _Interest, double _Normal_monthly_rate)
{
    //Gets time
    time_t CurrTimeInSec = time(0);
    tm *TempCurTime= localtime(&CurrTimeInSec);
    TempCurTime->tm_year += 1900;
    TempCurTime->tm_mon += 1;
    QDateTime CurTime;
    CurTime.setDate(QDate(TempCurTime->tm_year, TempCurTime->tm_mon, 1));

    QDateTime _Time = CurTime;
    Abnormal_Payment_Node *_node_Temp = _Head;



    double _current_Mortage_Amount = _Mortgage_Amount;
    double _Cumulative_Interest_Amount = 0.00;
    double _Principal_Paid_Amount = 0.00;
    Time_And_Date_Table* Data_Table = new Time_And_Date_Table;
    Data_Table->Balance_insertNode(_Time.toString("yyyy MM") , _current_Mortage_Amount);
    Data_Table->Cum_Interest_insertNode(_Time.toString("yyyy MM") , _Cumulative_Interest_Amount);
    Data_Table->Principal_Paid_insertNode(_Time.toString("yyyy MM") , _Principal_Paid_Amount);


    while(_current_Mortage_Amount > 0){
        double _Temp_Principal_Paid_Amount = 0.00;
        double Abnormal_Payment = 0.00;
        while(_node_Temp != NULL && _Time >= _node_Temp->Time){
            if(_Time == _node_Temp->Time){
                Abnormal_Payment += _node_Temp->Amount;
            }
            _node_Temp = _node_Temp->next;
        }
        double Monthly_Interest = _current_Mortage_Amount * interestRateCalculation(_Time, _Interest);

        _current_Mortage_Amount += Monthly_Interest;

        if(Abnormal_Payment + _Normal_monthly_rate <= _current_Mortage_Amount){
            _current_Mortage_Amount -= (_Normal_monthly_rate + Abnormal_Payment);
            if(_Normal_monthly_rate + Abnormal_Payment - Monthly_Interest > 0){

                _Cumulative_Interest_Amount += Monthly_Interest;

                _Principal_Paid_Amount += Abnormal_Payment + _Normal_monthly_rate - Monthly_Interest;
            }else{

                _Cumulative_Interest_Amount += Abnormal_Payment + _Normal_monthly_rate;

                _Principal_Paid_Amount += Abnormal_Payment + _Normal_monthly_rate - Monthly_Interest;
            }



        }else{
            _Principal_Paid_Amount += _current_Mortage_Amount;

            _Cumulative_Interest_Amount += Monthly_Interest;

            _current_Mortage_Amount = 0;




        }
        _Time = _Time.addMonths(1);
        if(_current_Mortage_Amount > 0){
            Data_Table->Balance_insertNode(_Time.toString("yyyy MM") , _current_Mortage_Amount);
            Data_Table->Cum_Interest_insertNode(_Time.toString("yyyy MM") , _Cumulative_Interest_Amount);
            Data_Table->Principal_Paid_insertNode(_Time.toString("yyyy MM") , _Principal_Paid_Amount);
        }else{
            Data_Table->Balance_insertNode(_Time.toString("yyyy MM") , 0.00);
            Data_Table->Cum_Interest_insertNode(_Time.toString("yyyy MM") , _Cumulative_Interest_Amount);
            Data_Table->Principal_Paid_insertNode(_Time.toString("yyyy MM") , _Mortgage_Amount);
        }
    }
    return Data_Table;
}

Time_And_Date_Table* BackgroundMethods::NM_Amortization_Calculations(double _Mortgage_Amount, double _Interest, double _Normal_monthly_rate)
{
    //Gets time
    time_t CurrTimeInSec = time(0);
    tm *TempCurTime= localtime(&CurrTimeInSec);
    TempCurTime->tm_year += 1900;
    TempCurTime->tm_mon += 1;
    QDateTime CurTime;
    CurTime.setDate(QDate(TempCurTime->tm_year, TempCurTime->tm_mon, 1));

    QDateTime _Time = CurTime;



    double _current_Mortage_Amount = _Mortgage_Amount;
    double _Cumulative_Interest_Amount = 0.00;
    double _Principal_Paid_Amount = 0.00;
    Time_And_Date_Table* Data_Table = new Time_And_Date_Table;
    Data_Table->Balance_insertNode(_Time.toString("yyyy MM") , _current_Mortage_Amount);
    Data_Table->Cum_Interest_insertNode(_Time.toString("yyyy MM") , _Cumulative_Interest_Amount);
    Data_Table->Principal_Paid_insertNode(_Time.toString("yyyy MM") , _Principal_Paid_Amount);


    while(_current_Mortage_Amount > 0){
        double _Temp_Principal_Paid_Amount = 0.00;
        double Monthly_Interest = _current_Mortage_Amount * interestRateCalculation(_Time, _Interest);

        _current_Mortage_Amount += Monthly_Interest;

        if(_Normal_monthly_rate <= _current_Mortage_Amount){
            _current_Mortage_Amount -= (_Normal_monthly_rate);
            if(_Normal_monthly_rate - Monthly_Interest > 0){

                _Cumulative_Interest_Amount += Monthly_Interest;

                _Principal_Paid_Amount += _Normal_monthly_rate - Monthly_Interest;
            }else{

                _Cumulative_Interest_Amount += _Normal_monthly_rate;

                _Principal_Paid_Amount += _Normal_monthly_rate - Monthly_Interest;
            }



        }else{
            _Principal_Paid_Amount += _current_Mortage_Amount;

            _Cumulative_Interest_Amount += Monthly_Interest;

            _current_Mortage_Amount = 0;




        }
        _Time = _Time.addMonths(1);
        if(_current_Mortage_Amount > 0){
            Data_Table->Balance_insertNode(_Time.toString("yyyy MM") , _current_Mortage_Amount);
            Data_Table->Cum_Interest_insertNode(_Time.toString("yyyy MM") , _Cumulative_Interest_Amount);
            Data_Table->Principal_Paid_insertNode(_Time.toString("yyyy MM") , _Principal_Paid_Amount);
        }else{
            Data_Table->Balance_insertNode(_Time.toString("yyyy MM") , 0.00);
            Data_Table->Cum_Interest_insertNode(_Time.toString("yyyy MM") , _Cumulative_Interest_Amount);
            Data_Table->Principal_Paid_insertNode(_Time.toString("yyyy MM") , _Mortgage_Amount);
        }
    }
    return Data_Table;
}
