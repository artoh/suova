/**************************************************************************
**  Mainpage.qml (of Suova)
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
**  MainPage.qml  28.6.2012
**************************************************************************/

import QtQuick 1.1
import com.nokia.meego 1.0
import suova 0.1

Page {
    tools: commonTools

    Label {
        id: label
        anchors.centerIn: parent
        text: qsTr("Hello world!")
        visible: false
    }

    Button
    {
        id: searchTypeButton
        text: "Search type"
        onClicked: {searchTypeSelectionDialog.open();}
    }



    SelectionDialog
    {
        id: searchTypeSelectionDialog
        titleText: qsTr("Search type")
        selectedIndex: 0

        model: ListModel
        {
            ListElement { name: "File name" }
            ListElement { name: "Contents" }
            ListElement { name: "Title" }
        }

    }


    TextField
    {
        id: searchTextField
        anchors.top: searchTypeButton.bottom
    }

    Button
    {
        id: fileTypeButton
        text: "File type"
        onClicked: {fileTypeSelectionDialog.open()}

        anchors.top: searchTextField.bottom
    }

    SelectionDialog
    {
        id: fileTypeSelectionDialog
        titleText: "File type"
        selectedIndex: 0

        model: ListModel
        {
            ListElement { name: "All files" }
            ListElement { name: "Text documents" }
            ListElement { name: "Image files" }
        }
    }

    Button
    {
        id: keywordButton
        text: "Keyword"
        onClicked: {
            keywordSelectionDialog.model.setQuery("SELECT DISTINCT ?k where {?f nie:keyword ?k . } ORDER BY ?k")
            keywordSelectionDialog.model.count = keywordSelectionDialog.model.rowCount()
            console.debug(keywordSelectionDialog.model.count)
            keywordSelectionDialog.open()
        }

        anchors.top: fileTypeButton.bottom

    }

    SelectionDialog
    {
        id: keywordSelectionDialog
        titleText: "Keyword"
        selectedIndex: 0


        model: SuovaQueryModel{
            property int count : 0




        }


//        delegate: Label {text: keywordSelectionDialog.model.result(index,0)
//      color: "white"}

//        model: ListModel
//        {
//            ListElement { name: "To be implemented"}
//        }
    }

    Button
    {
        id: tagButton
        text: "Tag"
        onClicked: {
            tagSelectionDialog.model.setQuery("SELECT  ?labels WHERE {   ?tags a nao:Tag ;     nao:prefLabel ?labels . } ORDER BY ASC(?labels)")
            tagSelectionDialog.model.count = tagSelectionDialog.model.rowCount()
            console.debug("Fetched tags")
            tagSelectionDialog.open()

           }

        anchors.top: keywordButton.bottom


    }


    SelectionDialog
    {
        id: tagSelectionDialog
        titleText: "Tag"
        selectedIndex: 0

        model: SuovaQueryModel
                {
                property int count : 0;

                }

    }


    Button{
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: label.bottom
            topMargin: 10
        }
        text: qsTr("Search")
        onClicked: {appWindow.pageStack.push(resultsPage)}
    }
}
