QT += core gui multimedia multimediawidgets widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DESTDIR = build
OBJECTS_DIR = build/obj
MOC_DIR = build/moc
RCC_DIR = build/rcc
UI_DIR = build/ui

QMAKE_BUNDLE_DATA = build

HEADERS += src/mainwindow.hpp\
           src/car_joy.h

TARGET = car_joy.out
TEMPLATE = app

SOURCES += src/main.cpp\
           src/car_joy.cpp\
           src/mainwindow.cpp

FORMS += src/mainwindow.ui

#QMAKE_CXXFLAGS += -g
#QMAKE_LFLAGS += -g
