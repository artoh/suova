/**************************************************************************
**  main.qml (of Suova)
**  Copyright (c) 2012 Heli Hyvättinen
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
**  main.qml  28.6.2012
**************************************************************************/

import QtQuick 1.1
import com.nokia.meego 1.0

PageStackWindow {
    id: appWindow

    initialPage: mainPage

    MainPage {
        id: mainPage
    }

    ResultsPage
    {
        id: resultsPage
    }

    AboutPage
    {
        id: aboutPage
    }

    FullFileInfoPage
    {
        id: fullFileInfoPage
    }

    ToolBarLayout {
        id: commonTools
        visible: true

        ToolIcon
        {
//            id: backTool
            iconId: "toolbar-back"
            visible: (pageStack.currentPage == mainPage) ? false : true
            onClicked:
            {
                pageStack.pop()
            }
        }

        ToolIcon {
            platformIconId: "toolbar-view-menu"
            anchors.right: (parent === undefined) ? undefined : parent.right
            onClicked: (myMenu.status === DialogStatus.Closed) ? myMenu.open() : myMenu.close()
        }
    }

    Menu {
        id: myMenu
        visualParent: pageStack
        MenuLayout {
            MenuItem
            {
                text: qsTr("About")
                onClicked: pageStack.push(aboutPage)
            }

        }
    }
}
