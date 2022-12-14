#-------------------------------------------------
#
# Project created by QtCreator 2019-08-10T17:16:23
#
#-------------------------------------------------

QT       += core gui concurrent
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ffmpage_http
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        atcpclient.cpp \
        httptools.cpp \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        atcpclient.h \
        ffmpeghead.h \
        httptools.h \
        mainwindow.h

FORMS += \
        mainwindow.ui

LIBS += -luser32

win32:CONFIG(release, debug|release): LIBS += -LD:/opencv/opencv/build/x64/vc15/lib/ -lopencv_world411
else:win32:CONFIG(debug, debug|release): LIBS += -LD:/opencv/opencv/build/x64/vc15/lib/ -lopencv_world411d
else:unix: LIBS += -LD:/opencv/opencv/build/x64/vc15/lib/ -lopencv_world411

INCLUDEPATH += D:/opencv/opencv/build/include
DEPENDPATH += D:/opencv/opencv/build/include

INCLUDEPATH += $$PWD/ffmpeg
include ($$PWD/ffmpeg/ffmpeg.pri)

DISTFILES += \
    needWord.txt

