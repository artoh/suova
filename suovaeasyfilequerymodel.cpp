/**************************************************************************
**  suovaeasyfilequerymodel.cpp (of Suova)
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
**  SuovaEasyFileQueryModel 10.7.2012
**************************************************************************/

#include "suovaeasyfilequerymodel.h"

SuovaEasyFileQueryModel::SuovaEasyFileQueryModel(QObject *parent) :
    SuovaFileQueryModel(parent)
{
}

void SuovaEasyFileQueryModel::setSearchType(QString type)
{
    searchType_ = type;
}

void SuovaEasyFileQueryModel::setFileType(QString type)
{
    fileType_ = type;
}

void SuovaEasyFileQueryModel::setSearchString(QString search)
{
    searchString_ = search;
}

void SuovaEasyFileQueryModel::setTag(QString tag)
{
    tag_ = tag;
}

void SuovaEasyFileQueryModel::setKeyword(QString keyword)
{
    keyword_ = keyword;
}

void SuovaEasyFileQueryModel::doQuery()
{


    // DIRTY test code to make searches! adapted from SuovaWindow code!!! =>> REALLY DIRTY

    QString typeWhere;
    QString keyWhere;
//    QString type = typeCombo_->itemData(typeCombo_->currentIndex()).toString(); //QML stuff
    if( !fileType_.isEmpty())
        typeWhere= QString("rdf:type '%1';").arg(fileType_);
//    QString keyword = keywordCombo_->itemData( keywordCombo_->currentIndex()).toString(); //QML stuff
    if( !keyword_.isEmpty())
        keyWhere = QString("nie:keyword '%1' ;").arg(keyword_);

//    QString tag = tagCombo_->itemData( tagCombo_->currentIndex()).toString();  //QML stuff
    if( !tag_.isEmpty())
        keyWhere += QString("nao:hasTag [nao:prefLabel '%1'] ; ").arg(tag_);

    // Test code (from SuovaWindow): full text search
    if( !searchString_.isEmpty())
    {
        QString where;
        // do full text seach
        if( searchType_=="fts:match")
            where = QString("{ ?f %2 %3 fts:match '%1*' } ").arg(searchString_).arg(typeWhere).arg(keyWhere);
        else
            where = QString("{ ?f %1  %4 %2 ?name . FILTER regex(?name, '%3')  }").arg(typeWhere).arg(searchType_).arg(searchString_).arg(keyWhere) ;
        setWhere(where);
    }
    else
        // do last accessedseach
    {
        keyWhere.clear();
        if( !keyword_.isEmpty())
            keyWhere = QString("; nie:keyword '%1' ").arg(keyword_);
        if( !tag_.isEmpty())
            keyWhere += QString(" ; nao:hasTag [nao:prefLabel '%1'] ").arg(tag_);
        if( fileType_.isEmpty())
            setWhere(QString("{ ?f nfo:fileLastAccessed ?pvm %1} ORDER BY DESC(?pvm) LIMIT 100 ").arg(keyWhere));
        else
            setWhere(QString("{ ?f nfo:fileLastAccessed ?pvm ; rdf:type '%1' %2} ORDER BY DESC(?pvm) LIMIT 100 ").arg(fileType_).arg(keyWhere));
   }
}
