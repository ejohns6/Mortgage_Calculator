#-------------------------------------------------
#
# Project created by QtCreator 2019-04-11T22:07:10
#
#-------------------------------------------------

QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Mortgage
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    backgroundmethods.cpp \
    abnorma_payment_node.cpp \
    time_and_date_table.cpp

HEADERS += \
        mainwindow.h \
    backgroundmethods.h \
    abnormal_payment_node.h \
    t_and_d_node.h \
    time_and_date_table.h

FORMS += \
        mainwindow.ui

copydata.commands = $(COPY_DIR) $$PWD/InputData.txt $$PWD/README.txt $$OUT_PWD
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    InputData.txt \
    README.txt

