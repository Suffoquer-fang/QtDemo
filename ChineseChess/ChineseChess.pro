#-------------------------------------------------
#
# Project created by QtCreator 2018-09-03T23:25:14
#
#-------------------------------------------------

QT       += core gui
QT += network
QT += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChineseChess
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        client.cpp \
    game.cpp \
    mapclass.cpp \
    gamewindow.cpp \
    paintwidget.cpp \
    controlwidget.cpp

HEADERS += \
        client.h \
    game.h \
    mapclass.h \
    stone.h \
    gamewindow.h \
    paintwidget.h \
    controlwidget.h

FORMS += \
        client.ui \
    gamewindow.ui \
    controlwidget.ui

RESOURCES += \
    res.qrc

DISTFILES += \
    IMG/dark.png \
    IMG/light.png \
    SOUND/Woman_jiangjun.mp3
