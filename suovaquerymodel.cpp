/**************************************************************************
**  suovaquerymodel.cpp
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
**  SuovaQueryModel  12.6.2012
**************************************************************************/

#include "suovaquerymodel.h"
#include <QDebug>



SuovaQueryModel::SuovaQueryModel(QObject *parent, QString query) :
    SuovaAbstractQueryModel(parent)
{
    if( !query.isEmpty())
        setQuery(query);
}

int SuovaQueryModel::rowCount(const QModelIndex& /* parent */) const
{
    return result_.count();
}

int SuovaQueryModel::columnCount(const QModelIndex& /* parent */) const
{
    if( result_.count())
        return result_.first().count();
    return 0;
}

QString SuovaQueryModel::result(const int row, const int column) const
{
    if( row >= 0 && row < rowCount() && column >= 0 && column < columnCount())
    {
        return result_.at(row).at(column);
    }

    return QString();   // Out of result set
}




QVariant SuovaQueryModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if( role == Qt::TextAlignmentRole)
        return int( Qt::AlignCenter | Qt::AlignVCenter);
    else if( role == Qt::DisplayRole)
    {
        if( orientation == Qt::Vertical)
            return QVariant(section+1);   // row number
        else
            return columnHeaders_.value(section);
    }

    return QVariant();
}



void SuovaQueryModel::clear()
{
    result_.clear();
}


void SuovaQueryModel::appendRow(const QStringList& rowData)
{
    result_.append( rowData);
}

bool SuovaQueryModel::setQuery(const QString &query)
{

//    qDebug() << "Setting Query";
    if( execQuery(query))
    {
//        qDebug() << "Query succeeded";
//        qDebug() << columnCount() << " columns";
//        qDebug() << rowCount() << "rows";
//        qDebug() << data(index(0,0),Qt::DisplayRole) << " <= data of first item";


        columnHeaders_.clear();

        // Try to analyze query to find column headers
        QStringList queryLine = query.split(" ");
        foreach(QString item, queryLine)
        {
            if( item.startsWith("WHERE"))
                return true;     // end of fields reached
            if( item.contains('?'))
                columnHeaders_.append(item);    // Item!
        }
        return true;
    }
//    qDebug() << "Query failed.";
    return false;
}
