#-------------------------------------------------
#
# Project created by QtCreator 2018-09-01T22:35:11
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = CancerAnalysis
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

SOURCES += \
        services/fileservice.cpp \
        services/floatservice.cpp \
        services/imageservice.cpp \
        services/itemsservice.cpp \
        services/stringservice.cpp \
        widgets/filewidget.cpp \
        mainwindow.cpp \
        main.cpp 

HEADERS += \
        services/fileservice.h \
        services/floatservice.h \
        services/imageservice.h \
        services/itemsservice.h \
        services/stringservice.h \
        widgets/filewidget.h \
        mainwindow.h \
        services.h 

FORMS += \
        mainwindow.ui \
        widgets/filewidget.ui

win32: RC_FILE = iconsource.rc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    sources.qrc
