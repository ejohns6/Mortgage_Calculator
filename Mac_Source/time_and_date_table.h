#ifndef TIME_AND_DATE_TABLE_H
#define TIME_AND_DATE_TABLE_H

#include <QtCore/QTextStream>

#include "t_and_d_node.h"

class Time_And_Date_Table
{
private:
    T_and_D_Node* Balance_Head = NULL;
    T_and_D_Node* Cum_Interest_Head = NULL;
    T_and_D_Node* Principal_Paid_Head = NULL;

public:
    Time_And_Date_Table();

    ~Time_And_Date_Table();

    void Balance_insertNode(QString Date, double Amount);

    T_and_D_Node* Balance_getHead();

    double Balance_getLastNode_Amount();

    void Cum_Interest_insertNode(QString Date, double Amount);

    T_and_D_Node* Cum_Interest_getHead();

    double Cum_Interest_getLastNode_Amount();

    void Principal_Paid_insertNode(QString Date, double Amount);

    T_and_D_Node* Principal_Paid_getHead();

    double Principal_Paid_getLastNode_Amount();
};

#endif // TIME_AND_DATE_TABLE_H
