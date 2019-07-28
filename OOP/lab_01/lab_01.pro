#-------------------------------------------------
#
# Project created by QtCreator 2019-04-02T16:51:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lab_01
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
    displaywidget.cpp \
    handler.cpp \
    geometry.cpp \
    object.cpp \
    io.cpp \
    exit.cpp \
    management.cpp \
    projection.cpp \
    check_entry.cpp

HEADERS += \
        mainwindow.h \
    displaywidget.h \
    mycolors.h \
    handler.h \
    geometry.h \
    object.h \
    io.h \
    exit.h \
    management.h \
    projection.h \
    check_entry.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource/fonts/fonts.qrc \
    resource/icons/icons.qrc \
    resource/styles/styles.qrc
