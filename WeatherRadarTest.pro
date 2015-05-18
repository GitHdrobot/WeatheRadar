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

LIBS    += -L ./lib/qextserialport -llibqextserialportd.a

#DEPENDPATH += ./lib
#DEPENDPATH += ./lib/qextserialport
#INCLUDEPATH += ./lib
#INCLUDEPATH += ./lib/qextserialport

SOURCES += main.cpp\
        mainwindow.cpp \
    dialogsetting.cpp \
    dialogsample.cpp \
    maindisplay.cpp \
    rvp900.cpp \
    fetchdatathread.cpp \
    dispdevice.cpp \
    sector.cpp \
    palette.cpp \
    uartcomm.cpp \

HEADERS  += mainwindow.h \
    dialogsetting.h \
    dialogsample.h \
    constcode.h \
    constRVP900.h \
    maindisplay.h \
    rvp900.h \
    fetchdatathread.h \
    dispdevice.h \
    sector.h \
    palette.h \
    uartcomm.h \
    headerctrl.h \
    lib/qextserialport/posix_qextserialport.h \
    lib/qextserialport/qextserialbase.h \
    lib/qextserialport/qextserialenumerator.h \
    lib/qextserialport/qextserialport.h \
    lib/qextserialport/win_qextserialport.h

FORMS    += mainwindow.ui \
    dialogsetting.ui \
    dialogsample.ui

RESOURCES += \
    WeatherRadarRes.qrc

RC_FILE += \
    weather.rc

CONFIG(debug, debug|release):LIBS  += -lqextserialportd
else:LIBS  += -lqextserialport

unix:DEFINES   = _TTY_POSIX_
win32:DEFINES  = _TTY_WIN_
