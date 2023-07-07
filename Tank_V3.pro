#-------------------------------------------------
#
# Project created by QtCreator 2023-05-31T11:16:09
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia

# windows icons
RC_ICONS = tank_icon.ico

# macOS icons
ICON = logo.icns

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tank_V3
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
        main.cpp \
        mainwindow.cpp \
    mypushbutton.cpp \
    selectionwindow.cpp \
    helpwindow.cpp \
    playwindow.cpp \
    stopwindow.cpp \
    bullet.cpp \
    config.cpp \
    enemy.cpp \
    tankbase.cpp \
    player.cpp \
    endwindow.cpp

HEADERS += \
        mainwindow.h \
    mypushbutton.h \
    selectionwindow.h \
    helpwindow.h \
    playwindow.h \
    stopwindow.h \
    bullet.h \
    config.h \
    enemy.h \
    tankbase.h \
    player.h \
    endwindow.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    source.qrc

