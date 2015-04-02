#-------------------------------------------------
#
# Project created by QtCreator 2015-03-03T11:18:53
#
#-------------------------------------------------

QT       += core gui
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WeatherRadarTest
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialogsetting.cpp \
    dialogsample.cpp \
    maindisplay.cpp \
    rvp900.cpp \
    fetchdatathread.cpp \
    dispdevice.cpp

HEADERS  += mainwindow.h \
    dialogsetting.h \
    dialogsample.h \
    constcode.h \
    constRVP900.h \
    maindisplay.h \
    rvp900.h \
    fetchdatathread.h \
    dispdevice.h

FORMS    += mainwindow.ui \
    dialogsetting.ui \
    dialogsample.ui

RESOURCES += \
    WeatherRadarRes.qrc

RC_FILE += \
    weather.rc


