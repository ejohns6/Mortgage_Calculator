#ifndef T_AND_D_NODE_H
#define T_AND_D_NODE_H

#include <QtCore/QTextStream>


struct T_and_D_Node
{
private:
    QString m_Date = "";
    double m_Amount = 0.0;
    T_and_D_Node *m_next = NULL;

public:
    T_and_D_Node(QString Date, double Amount)
        :m_Date(Date), m_Amount(Amount)
    {

    }

    void setNext(QString Date, double Amount){
        m_next = new T_and_D_Node(Date, Amount);
        return;
    }

    T_and_D_Node* getNext(){
        return(m_next);
    }

    QString getDate(){
        return(m_Date);
    }

    double getAmount(){
        return(m_Amount);
    }

    ~T_and_D_Node(){

    }



};

#endif // T_AND_D_NODE_H
