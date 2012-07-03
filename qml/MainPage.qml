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

    Component.onCompleted:
    {
        keywordSelectionDialog.model.setQuery("SELECT DISTINCT ?k where {?f nie:keyword ?k . } ORDER BY ?k")
        keywordSelectionDialog.model.count = keywordSelectionDialog.model.rowCount()
//        console.debug(keywordSelectionDialog.model.count)

        tagSelectionDialog.model.setQuery("SELECT  ?labels WHERE {   ?tags a nao:Tag ;     nao:prefLabel ?labels . } ORDER BY ASC(?labels)")
        tagSelectionDialog.model.count = tagSelectionDialog.model.rowCount()
//        console.debug("Fetched tags")


        keywordSelectionDialog.model.setQuery("SELECT DISTINCT ?k where {?f nie:keyword ?k . } ORDER BY ?k")
        keywordSelectionDialog.model.count = keywordSelectionDialog.model.rowCount()
//        console.debug(keywordSelectionDialog.model.count)

        tagSelectionDialog.model.setQuery("SELECT  ?labels WHERE {   ?tags a nao:Tag ;     nao:prefLabel ?labels . } ORDER BY ASC(?labels)")
        tagSelectionDialog.model.count = tagSelectionDialog.model.rowCount()
//        console.debug("Fetched tags")
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
            ListElement
            {
                name: "File name"
                ontology: "nfo:fileName"
            }
            ListElement
            {
                name: "Contents"
                ontology: "fts:match"
            }
            ListElement
            {
                name: "Title"
                ontology: "nie:title"
            }
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
            ListElement
            {
                name: "All files"
                ontology: ""
            }

            ListElement
            {
                name: "Text documents"
                ontology: "http://www.semanticdesktop.org/ontologies/2007/03/22/nfo#TextDocument"
            }

            ListElement
            {
                name: "Image files"
                ontology: "http://www.semanticdesktop.org/ontologies/2007/03/22/nfo#Image"
            }
        }
    }

    Button
    {
        id: keywordButton
        text: "Keyword"
        onClicked: {

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

    }

    Button
    {
        id: tagButton
        text: "Tag"
        onClicked: {

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
            top: tagButton.bottom
            topMargin: 10
        }
        text: qsTr("Search")
        onClicked: {pageStack.push(resultsPage)}
    }
}
