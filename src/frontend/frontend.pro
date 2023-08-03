QT       += core gui printsupport widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

qmake
TARGET = ../SmartCalc

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../backend/banking_calculations.c \
    ../backend/stack.c \
    ../backend/parsing.c \
    ../backend/calculate.c \
    credit.cpp \
    deposit.cpp \
    graph.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp

HEADERS += \
    ../backend/banking_calculations.h \
    ../backend/stack.h \
    ../backend/parsing.h \
    ../backend/calculate.h \
    credit.h \
    deposit.h \
    graph.h \
    mainwindow.h \
    qcustomplot.h


FORMS += \
    credit.ui \
    deposit.ui \
    graph.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target