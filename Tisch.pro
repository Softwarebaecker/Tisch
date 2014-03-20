#-------------------------------------------------
#
# Project created by QtCreator 2013-11-14T09:09:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tisch
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    propertieswindow.cpp \
    tracking.cpp \
    Properties.cpp \
    calibrationwindow.cpp \
    mouse.cpp \
    simulationswindow.cpp

HEADERS  += mainwindow.h \
    propertieswindow.h \
    tracking.h \
    Properties.h \
    calibrationwindow.h \
    mouse.h \
    simulationswindow.h

FORMS    += mainwindow.ui \
    propertieswindow.ui \
    calibrationwindow.ui \
    simulationswindow.ui



LIBS +=     -lopencv_core\
            -lopencv_highgui\
            -lopencv_imgproc\
            -lopencv_video\

CONFIG += link_pkgconfig
PKGCONFIG += x11

OTHER_FILES +=

QMAKE_CXXFLAGS += -O1
