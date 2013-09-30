#-------------------------------------------------
#
# Project created by QtCreator 2013-09-20T20:53:03
#
#-------------------------------------------------

QT       += core gui
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtPlayfield
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Booking.cpp \
    Account.cpp

HEADERS  += mainwindow.h \
    Booking.h \
    Account.h \
    initdb.h

FORMS    += mainwindow.ui
