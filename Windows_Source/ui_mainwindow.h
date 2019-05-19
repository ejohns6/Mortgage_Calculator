/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *CurrentMortgageAmount_Label;
    QLabel *InterestRate_Year_Label;
    QLabel *NormalMonthlyPayment_Label;
    QLineEdit *CurentMortgageAmount_lineEdit;
    QLabel *Percent1_Label;
    QLineEdit *InterestRate_Year_lineEdit;
    QLineEdit *NormalMonthlyPayment_lineEdit;
    QLabel *SpecificPayments_Label;
    QMenuBar *menuBar;
    QMenu *menumortgage_calculator;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(534, 643);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        CurrentMortgageAmount_Label = new QLabel(centralWidget);
        CurrentMortgageAmount_Label->setObjectName(QString::fromUtf8("CurrentMortgageAmount_Label"));
        CurrentMortgageAmount_Label->setGeometry(QRect(10, 20, 141, 16));
        CurrentMortgageAmount_Label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        InterestRate_Year_Label = new QLabel(centralWidget);
        InterestRate_Year_Label->setObjectName(QString::fromUtf8("InterestRate_Year_Label"));
        InterestRate_Year_Label->setGeometry(QRect(10, 50, 141, 16));
        InterestRate_Year_Label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        NormalMonthlyPayment_Label = new QLabel(centralWidget);
        NormalMonthlyPayment_Label->setObjectName(QString::fromUtf8("NormalMonthlyPayment_Label"));
        NormalMonthlyPayment_Label->setGeometry(QRect(10, 80, 141, 16));
        NormalMonthlyPayment_Label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        CurentMortgageAmount_lineEdit = new QLineEdit(centralWidget);
        CurentMortgageAmount_lineEdit->setObjectName(QString::fromUtf8("CurentMortgageAmount_lineEdit"));
        CurentMortgageAmount_lineEdit->setGeometry(QRect(160, 20, 341, 16));
        Percent1_Label = new QLabel(centralWidget);
        Percent1_Label->setObjectName(QString::fromUtf8("Percent1_Label"));
        Percent1_Label->setGeometry(QRect(500, 50, 16, 16));
        Percent1_Label->setAlignment(Qt::AlignCenter);
        InterestRate_Year_lineEdit = new QLineEdit(centralWidget);
        InterestRate_Year_lineEdit->setObjectName(QString::fromUtf8("InterestRate_Year_lineEdit"));
        InterestRate_Year_lineEdit->setGeometry(QRect(160, 50, 341, 16));
        NormalMonthlyPayment_lineEdit = new QLineEdit(centralWidget);
        NormalMonthlyPayment_lineEdit->setObjectName(QString::fromUtf8("NormalMonthlyPayment_lineEdit"));
        NormalMonthlyPayment_lineEdit->setGeometry(QRect(160, 80, 341, 16));
        SpecificPayments_Label = new QLabel(centralWidget);
        SpecificPayments_Label->setObjectName(QString::fromUtf8("SpecificPayments_Label"));
        SpecificPayments_Label->setGeometry(QRect(0, 110, 531, 20));
        SpecificPayments_Label->setAlignment(Qt::AlignCenter);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 534, 21));
        menumortgage_calculator = new QMenu(menuBar);
        menumortgage_calculator->setObjectName(QString::fromUtf8("menumortgage_calculator"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menumortgage_calculator->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        CurrentMortgageAmount_Label->setText(QApplication::translate("MainWindow", "Current mortgage Amount: $", nullptr));
        InterestRate_Year_Label->setText(QApplication::translate("MainWindow", "Interest Rate (yearly):", nullptr));
        NormalMonthlyPayment_Label->setText(QApplication::translate("MainWindow", "Normal Monthly Payment: $", nullptr));
        Percent1_Label->setText(QApplication::translate("MainWindow", "%", nullptr));
        SpecificPayments_Label->setText(QApplication::translate("MainWindow", "Specific Payments", nullptr));
        menumortgage_calculator->setTitle(QApplication::translate("MainWindow", "mortgage calculator", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
