#include "time_and_date_table.h"

Time_And_Date_Table::Time_And_Date_Table()
{

}

/*
int Node_Amount = 0;
T_and_D_Node Head = NULL;
*/

void Time_And_Date_Table::Balance_insertNode(QString Date, double Amount){
    //If Balance_head is empty
    if(Balance_getHead() == NULL){
        T_and_D_Node* node = new T_and_D_Node(Date,Amount);
        Balance_Head = node;
        return;
    }else{
        T_and_D_Node* temp_node = Balance_getHead();
        while(temp_node->getNext() != NULL){
            temp_node = temp_node->getNext();
        }
        temp_node->setNext(Date, Amount);
        return;
    }
}

T_and_D_Node* Time_And_Date_Table::Balance_getHead(){
    return(Balance_Head);
}

double Time_And_Date_Table::Balance_getLastNode_Amount(){
    T_and_D_Node* temp_node = Balance_getHead();
    while(temp_node->getNext() != NULL){
        temp_node = temp_node->getNext();
    }
    double Amount = temp_node->getAmount();
    return(Amount);
}

void Time_And_Date_Table::Cum_Interest_insertNode(QString Date, double Amount){
    //If Cum_Interest_head is empty
    if(Cum_Interest_getHead() == NULL){
        T_and_D_Node* node = new T_and_D_Node(Date,Amount);
        Cum_Interest_Head = node;
        return;
    }else{
        T_and_D_Node* temp_node = Cum_Interest_getHead();
        while(temp_node->getNext() != NULL){
            temp_node = temp_node->getNext();
        }
        temp_node->setNext(Date, Amount);
        return;
    }
}

T_and_D_Node* Time_And_Date_Table::Cum_Interest_getHead(){
    return(Cum_Interest_Head);
}

double Time_And_Date_Table::Cum_Interest_getLastNode_Amount(){
    T_and_D_Node* temp_node = Cum_Interest_getHead();
    while(temp_node->getNext() != NULL){
        temp_node = temp_node->getNext();
    }
    double Amount = temp_node->getAmount();
    return(Amount);
}

void Time_And_Date_Table::Principal_Paid_insertNode(QString Date, double Amount){
    //If Principal_Paid_head is empty
    if(Principal_Paid_getHead() == NULL){
        T_and_D_Node* node = new T_and_D_Node(Date,Amount);
        Principal_Paid_Head = node;
        return;
    }else{
        T_and_D_Node* temp_node = Principal_Paid_getHead();
        while(temp_node->getNext() != NULL){
            temp_node = temp_node->getNext();
        }
        temp_node->setNext(Date, Amount);
        return;
    }
}

T_and_D_Node* Time_And_Date_Table::Principal_Paid_getHead(){
    return(Principal_Paid_Head);
}

double Time_And_Date_Table::Principal_Paid_getLastNode_Amount(){
    T_and_D_Node* temp_node = Principal_Paid_getHead();
    while(temp_node->getNext() != NULL){
        temp_node = temp_node->getNext();
    }
    double Amount = temp_node->getAmount();
    return(Amount);
}
