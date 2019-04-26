#ifndef ABNORMAL_PAYMENT_NODE_H
#define ABNORMAL_PAYMENT_NODE_H

#include <QtCore/QDateTime>

#include <iostream>


class Abnormal_Payment_Node
{
public:
    bool inUse = false;

    QDateTime Time;
    double Amount = 0;
    Abnormal_Payment_Node *next = NULL;

    static void Insert_Abnormal_pay_Node(Abnormal_Payment_Node **Head, Abnormal_Payment_Node *N_node);

    void print_Abnormal_payments(Abnormal_Payment_Node *Head);

    int count_Abnormal_payments(Abnormal_Payment_Node *Head);


    void destory_list(Abnormal_Payment_Node *Head);



};

#endif // ABNORMA_PAYMENT_NODE_H
