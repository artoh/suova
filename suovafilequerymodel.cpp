/**************************************************************************
**  suovafilequerymodel.cpp
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
**  SuovaFileQueryModel  13.6.2012
**************************************************************************/

#include "suovafilequerymodel.h"

#include <QIcon>

SuovaFileQueryModel::SuovaFileQueryModel(QObject *parent, const QString &where) :
    SuovaQueryModel(parent)
{
    if( !where.isEmpty())
        setWhere(where);
}


bool SuovaFileQueryModel::setWhere(const QString &where)
{
    // query with file info headers and custom where
    QString query = QString("SELECT %1 WHERE  %2 ").arg(SuovaFileInfo::SelectFields).arg(where);

    return setQuery(query);

}

void SuovaFileQueryModel::appendRow(const QStringList &rowData)
{
    // append SuovaFileInfo object
    files_.append( SuovaFileInfo(rowData) );
}


void SuovaFileQueryModel::clear()
{
    files_.clear();
}

int SuovaFileQueryModel::rowCount(const QModelIndex &) const
{
    return files_.count();
}

int SuovaFileQueryModel::columnCount(const QModelIndex &) const
{
    // File, Modified and Size
    return 3;
}

QVariant SuovaFileQueryModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if( role == Qt::TextAlignmentRole)
        return int( Qt::AlignCenter | Qt::AlignVCenter);
    else if( role == Qt::DisplayRole)
    {
        if( orientation == Qt::Vertical)
            return QVariant(section+1);   // row number
        else
        {
            switch(section)
            {
            case 0 : return tr("File");
            case 1: return tr("Modified");
            case 2: return tr("Size");

            }
        }
    }

    return QVariant();
}


QVariant SuovaFileQueryModel::data(const QModelIndex &index, int role) const
{
    if( !index.isValid())
        return QVariant();

    if( role == Qt::TextAlignmentRole)
    {
        if( index.column()==0)
            return int( Qt::AlignLeft | Qt::AlignTop);
        else if( index.column() == 1)
            return int( Qt::AlignCenter | Qt::AlignTop);
        return int( Qt::AlignRight | Qt::AlignTop);
    }
    else if( role == Qt::DisplayRole)
    {
        return result( index.row(), index.column());
    }
    else if( role == Qt::DecorationRole && index.column() == 0)
    {
        QIcon icon = QIcon( QString(":/mime/pic/%1.png").arg( files_.at(index.row()).mimetype().replace('/','-') )  );
        return icon;
    }

    return QVariant();
}

QString SuovaFileQueryModel::result(const int row, const int column) const
{
    if( row >= 0 && row < rowCount())
    {
        switch( column )
        {
        case 0:
            if( files_.at(row).title().isEmpty())
                return files_.at(row).fileName();
            else
                return files_.at(row).title();
        case 1:
            return files_.at(row).modified().date().toString(Qt::SystemLocaleShortDate);
        case 2:
            int bytes = files_.at(row).bytes();
            if( bytes < 1024 )
                return tr("%1 b").arg(bytes);
            if( bytes < 1024 * 1024)
                return tr("%1 k").arg(bytes / 1024);
            return tr("%1 MB").arg( bytes / (1024 * 1024));
        }
    }
    return QString();
}
