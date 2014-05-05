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
    simulationswindow.cpp \
    paintwindow.cpp \
    ball.cpp \
    pannel.cpp \
    pongwindow.cpp

HEADERS  += mainwindow.h \
    propertieswindow.h \
    tracking.h \
    Properties.h \
    calibrationwindow.h \
    mouse.h \
    simulationswindow.h \
    paintwindow.h \
    ball.h \
    pannel.h \
    pongwindow.h

FORMS    += mainwindow.ui \
    propertieswindow.ui \
    calibrationwindow.ui \
    simulationswindow.ui \
    paintwindow.ui \
    pongwindow.ui



LIBS +=     -lopencv_core\
            -lopencv_highgui\
            -lopencv_imgproc\
            -lopencv_video\
            -lXtst -lX11

CONFIG += link_pkgconfig\
           debug c++11

PKGCONFIG += x11

OTHER_FILES +=

QMAKE_CXXFLAGS += -O1
