/**************************************************************************
**  AboutPage.qml (of Suova)
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
**  AboutPage 8.8.2012
**************************************************************************/

// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import com.nokia.meego 1.0

Page
{
    tools: commonTools

    Label
    {
        id: title
        text: "Suova 0.0.1"
    }
    Label
    {
        id: explanation
        text: "A Meta Tracker search frontend"
        anchors.top: title.bottom
    }
    Label
    {
        id: authors
        text: "© Arto Hyvättinen & Heli Hyvättinen 2012"
        anchors.top: explanation.bottom
    }

    Label
    {
        id: license
        text: "License: General Public License 3.<br>The source code is available from<br><a href=\"https://github.com/artoh/suova/tree/harmattan\">https://github.com/artoh/suova/tree/harmattan</a>"
        onLinkActivated: Qt.openUrlExternally(link)
        anchors.top: authors.bottom
        wrapMode: Text.Wrap
        textFormat: Text.RichText
    }


}
