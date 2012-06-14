/**************************************************************************
**  suovafileinfo.cpp
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
**  SuovaFileInfo  12.6.2012
**************************************************************************/

#include "suovafileinfo.h"
#include "suovaquerymodel.h"

SuovaFileInfo::SuovaFileInfo(QStringList data) :
    allInformationFetched_(false), tagsFetched_(false)
{
    if( data.count() > 8)
    {
        // Data MUST be in correct order!!!
        QStringListIterator iter(data);

        urn_ = iter.next(); // 1. field: urn
        url_ = iter.next(); // 2. field: url
        filename_ = iter.next(); // 3. field: file name
        title_ = iter.next(); // 4. field: file title
        mimetype_ = iter.next(); // 5. field: mime type
        created_ = QDateTime::fromString(iter.next(), Qt::ISODate); // 6. created
        modified_ = QDateTime::fromString(iter.next(), Qt::ISODate); // 7. modified
        accessed_ = QDateTime::fromString(iter.next(), Qt::ISODate); // 8. accessed
        bytes_ = iter.next().toInt(); // 9. file size in bytes

        fetchTags();
        fetchAllInformation();
    }
}


QString SuovaFileInfo::information(QString key) const
{
    return information_.value(key);
}

QStringList SuovaFileInfo::informations(QString key) const
{
    return information_.values(key);
}

QStringList SuovaFileInfo::tags() const
{
    return tags_;
}


void SuovaFileInfo::fetchAllInformation()
{
    SuovaQueryModel results;
    QString queryString = QString("SELECT ?predicate ?object ( EXISTS { ?predicate rdfs:range [ rdfs:subClassOf rdfs:Resource ] } ) WHERE { <%1> ?predicate ?object }").arg(urn());

    if(results.setQuery(queryString))
    {
        // Fetch query from model
        for(int i=0; i < results.rowCount(); i++)
        {
            QString key = results.result(i,0);
            QString value = results.result(i,1);
            information_.insertMulti(key, value);
        }
        allInformationFetched_ = true;
    }
}

void SuovaFileInfo::fetchTags()
{
    if( tagsFetched_)
        return;

    SuovaQueryModel tagQuery;
    QString queryString = QString("SELECT ?tags ?labels WHERE { <%1>   nao:hasTag ?tags . ?tags a nao:Tag ; nao:prefLabel ?labels . } ORDER BY ASC(?labels)").arg(urn());

    if( tagQuery.setQuery(queryString))
    {
        // Fetch tags from model
        for( int i=0; i < tagQuery.rowCount(); i++)
            tags_.append(tagQuery.result(i,1));
    }
    tagsFetched_ = true;
}

const QString SuovaFileInfo::SelectFields = "?f nie:url(?f) nfo:fileName(?f) nie:title(?f) nie:mimeType(?f) "
        "nie:contentCreated(?f) nfo:fileLastModified(?f) nfo:fileLastAccessed(?f) nfo:fileSize(?f)";
