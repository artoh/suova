/**************************************************************************
**  main.cpp
**  Copyright (c) 2012 Arto Hyvättinen 
**
**  This program is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  See <http://www.gnu.org/licenses/>
**
**    12.6.2012
**************************************************************************/

#include <QtGui/QApplication>
#include "suovawindow.h"
#include <qplatformdefs.h> // to recognize MEEGO_EDITION_HARMATTAN
#include "qmlapplicationviewer.h"
#include <QtDeclarative/QDeclarativeView>

int main(int argc, char *argv[])
{
    //Desktop version

#ifndef MEEGO_EDITION_HARMATTAN

    QApplication a(argc, argv);

    SuovaWindow w;
    w.show();
    return a.exec();
#endif
    

    //Harmattan version

#ifdef MEEGO_EDITION_HARMATTAN
    QScopedPointer<QApplication> app(createApplication(argc, argv));

//    QmlApplicationViewer viewer;
    QDeclarativeView view;
//    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
//    viewer.setMainQmlFile(QUrl("qrc:/qml/main.qml"));
//    viewer.showExpanded();
    view.setSource(QUrl("qrc:/qml/main.qml"));
    view.show();

    return app->exec();
#endif


}
