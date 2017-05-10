#-------------------------------------------------
#
# Project created by QtCreator 2017-05-09T23:19:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WeatherData
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    line.cpp \
    table.cpp \
    tablewindow.cpp

HEADERS  += mainwindow.h \
    line.h \
    table.h \
    tablewindow.h

FORMS    += mainwindow.ui \
    tablewindow.ui
