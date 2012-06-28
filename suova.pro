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
    suovaabstractfileinfo.cpp \
    suovasparqlwidget.cpp

HEADERS  += suovawindow.h \
    suovaquerymodel.h \
    suovafileinfo.h \
    suovafilequerymodel.h \
    suovaabstractquerymodel.h \
    suovafilefullinfo.h \
    suovaabstractfileinfo.h \
    suovasparqlwidget.h

# Please do not modify the following two lines. Required for deployment.
include(qmlapplicationviewer/qmlapplicationviewer.pri)
qtcAddDeployment()

OTHER_FILES += \
    README.txt \
    pic/suova.png \
    pic/suova.svg \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/manifest.aegis \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog \
    qml/Suova/MainPage.qml \
    qml/main.qml \
    qml/MainPage.qml \
    qml/ResultsPage.qml

RESOURCES += \
    pictures.qrc \
    qml.qrc

contains(MEEGO_EDITION,harmattan) {
    target.path = /opt/suova/bin
    INSTALLS += target

# Speed up launching on MeeGo/Harmattan when using applauncherd daemon
CONFIG += qdeclarative-boostable

## Add more folders to ship with the application, here
#folder_01.source = qml/Suova
#folder_01.target = qml
#DEPLOYMENTFOLDERS = folder_01

}



