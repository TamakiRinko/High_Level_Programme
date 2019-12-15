#-------------------------------------------------
#
# Project created by QtCreator 2019-12-11T21:08:49
#
#-------------------------------------------------

QT       += core gui webenginewidgets

include(./QHotkey-master/qhotkey.pri)

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MarkDownUI
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
    parser.cpp \
    values.cpp \
    htmlwindow.cpp \
    circle.cpp \
    curve.cpp \
    ellipse.cpp \
    eraser.cpp \
    graphics.cpp \
    linesegment.cpp \
    paint2dwidget.cpp \
    polygon.cpp \
    randomline.cpp \
    painterwindow.cpp \
    sizeinfo.cpp \
    screenshot.cpp \
    textedit.cpp

HEADERS += \
        mainwindow.h \
    parser.h \
    htmlwindow.h \
    circle.h \
    curve.h \
    ellipse.h \
    eraser.h \
    graphics.h \
    linesegment.h \
    paint2dwidget.h \
    polygon.h \
    randomline.h \
    painterwindow.h \
    screenshot.h \
    sizeinfo.h \
    textedit.h

FORMS += \
        mainwindow.ui \
    htmlwindow.ui \
    painterwindow.ui \
    sizeinfo.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    operations.qrc \
    backgrounds.qrc
