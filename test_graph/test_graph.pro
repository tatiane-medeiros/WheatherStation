#-------------------------------------------------
#
# Project created by QtCreator 2017-05-03T14:36:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = test_graph
TEMPLATE = app


SOURCES += main.cpp\
    qcustomplot.cpp \
    weatherdata.cpp \
    graphwindow.cpp\
    line.cpp\
    table.cpp


HEADERS  += \
    qcustomplot.h \
    weatherdata.h \
    graphwindow.h \
    line.h\
    table.h

FORMS    += \
    graphwindow.ui
