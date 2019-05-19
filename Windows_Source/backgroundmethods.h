#ifndef BACKGROUNDMETHODS_H
#define BACKGROUNDMETHODS_H

#include "abnormal_payment_node.h"
#include "time_and_date_table.h"

class BackgroundMethods
{
public:
    static double interestRateCalculation(QDateTime _Time, double _Interest);
    static Time_And_Date_Table* M_Amortization_Calculations(Abnormal_Payment_Node *_Head, double _Mortgage_Amount, double _Interest, double _Normal_monthly_rate);

    static Time_And_Date_Table* NM_Amortization_Calculations(double _Mortgage_Amount, double _Interest, double _Normal_monthly_rate);
};




#endif // BACKGROUNDMETHODS_H
