TEMPLATE = app
TARGET = myMoneyJournal
INCLUDEPATH += .
QT += sql widgets

# Input
HEADERS += src/Database.h src/mainwindow.h
FORMS += src/mainwindow.ui
SOURCES += src/Database.cpp src/main.cpp src/mainwindow.cpp
