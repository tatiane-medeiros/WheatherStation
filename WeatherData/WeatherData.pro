#-------------------------------------------------
#
# Project created by QtCreator 2017-05-09T23:19:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = WeatherData
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    line.cpp \
    table.cpp \
    tablewindow.cpp\
    qcustomplot.cpp \
    graphwindow.cpp


HEADERS  += mainwindow.h \
    line.h \
    table.h \
    tablewindow.h\
    qcustomplot.h\
   # datafunctions.h \
    graphwindow.h

FORMS    += mainwindow.ui \
    tablewindow.ui \
    graphwindow.ui

RC_FILE += dialogo.rc
