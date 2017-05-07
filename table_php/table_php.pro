#-------------------------------------------------
#
# Project created by QtCreator 2017-04-21T20:30:52
#
#-------------------------------------------------

QT    += core gui
QT    += widgets

TARGET = table_php
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    table.cpp \
    line.cpp \
    tablewindow.cpp

HEADERS += \
    table.h \
    line.h \
    tablewindow.h

FORMS += \
    tablewindow.ui
