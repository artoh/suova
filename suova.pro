#-------------------------------------------------
#
# Project created by QtCreator 2012-06-12T21:19:07
#
#-------------------------------------------------

QT       += core gui  dbus

TARGET = suova
TEMPLATE = app


SOURCES += main.cpp\
        suovawindow.cpp \
    suovaquerymodel.cpp \
    suovafileinfo.cpp \
    suovafilequerymodel.cpp \
    suovaabstractquerymodel.cpp \
    suovafilefullinfo.cpp \
    suovaabstractfileinfo.cpp

HEADERS  += suovawindow.h \
    suovaquerymodel.h \
    suovafileinfo.h \
    suovafilequerymodel.h \
    suovaabstractquerymodel.h \
    suovafilefullinfo.h \
    suovaabstractfileinfo.h

OTHER_FILES += \
    README.txt \
    pic/suova.png

RESOURCES += \
    pictures.qrc
