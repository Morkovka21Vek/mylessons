QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = car_joy.out
TEMPLATE = app

SOURCES += main.cpp \
           car_joy.cpp

FORMS += mainwindow.ui
