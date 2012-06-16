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
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/manifest.aegis \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog

RESOURCES += \
    pictures.qrc

contains(MEEGO_EDITION,harmattan) {
    target.path = /opt/suova/bin
    INSTALLS += target
}
