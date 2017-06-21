#-------------------------------------------------
#
# Project created by QtCreator 2017-06-08T19:09:51
#
#-------------------------------------------------

QT       += core gui svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Mort
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

RC_FILE = mort.rc
ICON = mort.icns

CONFIG += c++11

SOURCES += \
        main.cpp \
        ui/gamewindow.cpp \
    game_objects/user.cpp \
    ui/aboutdialog.cpp \
    game_objects/timer.cpp \
    ui/levelscene.cpp \
    game_objects/player.cpp \
    game_objects/goal.cpp \
    ui/level.cpp \
    game_objects/abstractblock.cpp \
    game_objects/clockfacade.cpp \
    ui/button.cpp

HEADERS += \
        ui/gamewindow.h \
    game_objects/user.h \
    ui/aboutdialog.h \
    game_objects/clock.h \
    game_objects/timer.h \
    ui/levelscene.h \
    game_objects/player.h \
    game_objects/goal.h \
    ui/level.h \
    game_objects/abstractblock.h \
    game_objects/abstractblockbuilder.h \
    game_objects/blockbuilder.h \
    game_objects/blockwaiter.h \
    game_objects/brokenblockbuilder.h \
    game_objects/clockfacade.h \
    ui/button.h

FORMS += \
        ui/gamewindow.ui \
    ui/aboutdialog.ui

RESOURCES += \
    images.qrc \
    config.qrc

