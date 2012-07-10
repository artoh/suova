/**************************************************************************
**  suovafilefullinfo.cpp
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
**  SuovaFileFullInfo  15.6.2012
**************************************************************************/

#include "suovafilefullinfo.h"
#include "suovaquerymodel.h"

#include <QDateTime>
#include <QString>


SuovaFileFullInfo::SuovaFileFullInfo(QString urn, QObject *parent) :
    SuovaAbstractQueryModel(parent), SuovaAbstractFileInfo()
{
    urn_ = urn;

    QString queryString = QString("SELECT ?predicate ?object  WHERE { <%1> ?predicate ?object }").arg(urn);

    // Use model query to get all the information.
    execQuery(queryString);

    // Get the tags, using querymodel
    SuovaQueryModel tagQuery;
    queryString = QString("SELECT ?tags ?labels WHERE { <%1>   nao:hasTag ?tags . ?tags a nao:Tag ; nao:prefLabel ?labels . } ORDER BY ASC(?labels)").arg(urn);

    if( tagQuery.setQuery(queryString))
    {
        // Fetch tags from model
        for( int i=0; i < tagQuery.rowCount(); i++)
        {
            information_.insertMulti("tag",tagQuery.result(i,1));
        }
    }
}



QVariant SuovaFileFullInfo::data(const QModelIndex &index, int role) const
{
    if( role == Qt::DisplayRole)
    {
        if( index.column() == 0)
            return information_.keys().at( index.row() );

        return information_.values().at( index.row() );
    }
    return QVariant();
}

QString SuovaFileFullInfo::result(const int row, const int column) const
{
    if( row < 0 || row >= rowCount() || column < 0 || column >= columnCount())
        return QString(); // Out of table

    if( column == 0)
        return information_.keys().at(row);

    return information_.values().at(row).toString();
}

int SuovaFileFullInfo::rowCount(const QModelIndex &) const
{
    return information_.count();
}

int SuovaFileFullInfo::columnCount(const QModelIndex&) const
{
    return 2;
}

QVariant SuovaFileFullInfo::headerData(int section, Qt::Orientation orientation, int role) const
{
    if( role == Qt::DisplayRole)
    {
        if( orientation == Qt::Vertical)
            return section + 1;

        if( section == 0)
            return tr("Key");
        return tr("Value");
    }
    return QVariant();
}

QVariant SuovaFileFullInfo::information(const QString &key) const
{
    // If there is more than one fields with this key,
    // return a string contaning all them: one, two
    if( information_.count(key) > 1)
    {
        QList<QVariant> list = informations(key);
        QStringList stringList;
        foreach( QVariant variant, list)
            stringList.append(variant.toString());
        QString asString = stringList.join(", ");
        return asString;
    }
    return information_.value(key);
}

QList<QVariant> SuovaFileFullInfo::informations(const QString &key) const
{
    return information_.values(key);
}

QStringList SuovaFileFullInfo::allKeys() const
{
    return information_.keys();
}

QList<QVariant> SuovaFileFullInfo::allInformation() const
{
    return information_.values();
}



void SuovaFileFullInfo::appendRow(const QStringList &rowData)
{
    if( rowData.count() < 2)
        return; // Invalid row

    QString key = withoutContext( rowData.at(0) );
    QString data = rowData.at(1);

    // Try to convert integer or datetime, if fails, string
    bool isInteger;
    int asInteger = data.toInt(&isInteger);

    if( isInteger)
    {
        information_.insertMulti(key, QVariant(asInteger));
        return;
    }

    QDateTime asDateTime = QDateTime::fromString( data, Qt::ISODate);
    if( asDateTime.isValid())
    {
        information_.insertMulti(key, QVariant(asDateTime));
        return;
    }

    information_.insertMulti(key, data);

}
