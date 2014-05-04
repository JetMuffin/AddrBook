#-------------------------------------------------
#
# Project created by QtCreator 2014-04-27T22:01:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = addrbook
TEMPLATE = app


SOURCES += main.cpp\
        addrbook.cpp \
    addrdialog.cpp

HEADERS  += addrbook.h \
    hash.h \
    addrdialog.h

FORMS    += addrbook.ui \
    addrdialog.ui

RESOURCES += \
    icon.qrc \
    qss.qrc \
    img.qrc
RC_FILE = addrbook.rc

