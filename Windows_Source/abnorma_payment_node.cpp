#include <QtCore/QDateTime>

#include <iostream>
#include <ctime>


#include "backgroundmethods.h"


void Abnormal_Payment_Node::Insert_Abnormal_pay_Node(Abnormal_Payment_Node **Head, Abnormal_Payment_Node *N_node)
{
    //Gets time
    time_t CurrTimeInSec = time(0);
    tm *TempCurTime= localtime(&CurrTimeInSec);
    TempCurTime->tm_year += 1970;
    TempCurTime->tm_mon += 1;
    QDateTime CurTime;
    CurTime.setDate(QDate(TempCurTime->tm_year, TempCurTime->tm_mon, 0));


    //Case 1: if the year is before current year
    //Case 2: if the month is before the current month before if the current year is the same as the year
    if(N_node->Time < CurTime){
        //cout << "Payment at " << N_node->Month << ", " << N_node->Year << " is an invalid date." << endl;
        delete N_node;
        return;
    }

    //Add case for when money is negative (maybe a line of credit)

    //Case 1: If there is no node
    if((*Head)->next == NULL && (*Head)->inUse == false){
        (*Head)->Time = N_node->Time;
        (*Head)->inUse = true;
        (*Head)->Amount = N_node->Amount;
        delete N_node;
        //delete the node
    }else if(N_node->Time < (*Head)->Time){
        //Case 2: If it before the the year
        //Case 3: If it the same year and an earlier month
        N_node->next = *Head;
        *Head = N_node;
    }else{
        //Case 4/5/6: If it is same year and month or if it is later or if it is the last one
        Abnormal_Payment_Node *temp = (*Head);
        while(temp->next != NULL){
            if(N_node->Time < temp->next->Time){
                N_node->next = temp->next;
                temp->next = N_node;
                return;
            }
            temp = temp->next;
        }
        temp->next = N_node;
    }
    return;

}

void Abnormal_Payment_Node::print_Abnormal_payments(Abnormal_Payment_Node *Head){
    //cout << "Abnormal Payments" << endl;
    Abnormal_Payment_Node *temp = Head;
    while(temp != NULL){
        //cout << "Payment: $" << temp->Amount << "\t\t Date: " << temp->Month << ", " << temp->Year << endl;
        temp = temp->next;
    }
    return;
}

int Abnormal_Payment_Node::count_Abnormal_payments(Abnormal_Payment_Node *Head){
    int _amount = 0;
    Abnormal_Payment_Node *temp = Head;
    while(temp != NULL){
        _amount += 1;
        temp = temp->next;
    }
    return(_amount);
}


void Abnormal_Payment_Node::destory_list(Abnormal_Payment_Node *Head){
    Abnormal_Payment_Node *temp = Head;
    while(temp != NULL){
        Head = Head->next;
        free(temp);
        temp = Head;
    }
    Head = NULL;
}
